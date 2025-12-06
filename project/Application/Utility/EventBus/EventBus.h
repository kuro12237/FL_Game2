#pragma once

#include <atomic>
#include <functional>
#include <mutex>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <utility>
#include <iostream>

/* イベントバス */
class EventBus
{

 public:
   using ListenerID = uint64_t;

 private: // シングルトン
   EventBus() = default;
   ~EventBus() = default;

   EventBus(const EventBus &) = delete;
   EventBus(EventBus &&) = delete;
   EventBus &operator=(const EventBus &) = delete;
   EventBus &operator=(EventBus &&) = delete;

 public:
   /// <summary>
   /// インスタンス取得
   /// </summary>
   static EventBus *Get()
   {
      static EventBus instance;
      return &instance;
   }

   /// <summary>
   /// イベントを登録し、リスナーIDを返す
   /// </summary>
   template <typename EventType, typename F> ListenerID Bind(F &&listener)
   {
      ListenerID id = ++idCounter_;

      auto wrapper = std::function<void(const void *)>([listener = std::forward<F>(listener)](const void *e) mutable {
         if constexpr (std::is_invocable_v<F, const EventType &>) {
            // 引数付き
            listener(*static_cast<const EventType *>(e));
         }
         else if constexpr (std::is_invocable_v<F>) {
            // 引数なし
            listener();
         }
         else {
            static_assert(std::is_invocable_v<F, const EventType &> || std::is_invocable_v<F>, "Bind: 無効なリスナー型です。void() または void(const EventType&) を登録してください。");
         }
      });

      listeners_[std::type_index(typeid(EventType))].push_back({id, std::move(wrapper)});

      return id;
   }

   /// <summary>
   /// イベント発行
   /// </summary>
   template <typename EventType> void Dispatch(const EventType &event) const
   {
      auto it = listeners_.find(std::type_index(typeid(EventType)));
      if (it == listeners_.end())
         return;

      for (const auto &pair : it->second) {
         pair.fn(&event);
      }
   }

   /// <summary>
   /// 特定のリスナーだけ削除（Unbind）
   /// </summary>
   template <typename EventType> void Unbind(ListenerID id)
   {
      auto it = listeners_.find(std::type_index(typeid(EventType)));
      if (it == listeners_.end())
         return;

      auto &vec = it->second;
      vec.erase(std::remove_if(vec.begin(), vec.end(), [id](const ListenerData &data) { return data.id == id; }), vec.end());
   }

   /// <summary>
   /// 全てのリスナー削除
   /// </summary>
   void Clear() { listeners_.clear(); }

 private:
   struct ListenerData
   {
      ListenerID id;
      std::function<void(const void *)> fn;
   };

   std::unordered_map<std::type_index, std::vector<ListenerData>> listeners_;
   ListenerID idCounter_ = 0;
};