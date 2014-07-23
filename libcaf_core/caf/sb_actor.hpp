/******************************************************************************
 *                       ____    _    _____                                   *
 *                      / ___|  / \  |  ___|    C++                           *
 *                     | |     / _ \ | |_       Actor                         *
 *                     | |___ / ___ \|  _|      Framework                     *
 *                      \____/_/   \_|_|                                      *
 *                                                                            *
 * Copyright (C) 2011 - 2014                                                  *
 * Dominik Charousset <dominik.charousset (at) haw-hamburg.de>                *
 *                                                                            *
 * Distributed under the terms and conditions of the BSD 3-Clause License or  *
 * (at your option) under the terms and conditions of the Boost Software      *
 * License 1.0. See accompanying files LICENSE and LICENCE_ALTERNATIVE.       *
 *                                                                            *
 * If you did not receive a copy of the license files, see                    *
 * http://opensource.org/licenses/BSD-3-Clause and                            *
 * http://www.boost.org/LICENSE_1_0.txt.                                      *
 ******************************************************************************/

#ifndef CAF_FSM_ACTOR_HPP
#define CAF_FSM_ACTOR_HPP

#include <utility>
#include <type_traits>

#include "caf/event_based_actor.hpp"

namespace caf {

/**
 * @brief A base class for state-based actors using the
 *    Curiously Recurring Template Pattern
 *    to initialize the derived actor with its @p init_state member.
 * @tparam Derived Direct subclass of @p sb_actor.
 */
template <class Derived, class Base = event_based_actor>
class sb_actor : public Base {

  static_assert(std::is_base_of<event_based_actor, Base>::value,
          "Base must be event_based_actor or a derived type");

 protected:

  using combined_type = sb_actor;

 public:

  /**
   * @brief Overrides {@link event_based_actor::make_behavior()} and sets
   *    the initial actor behavior to <tt>Derived::init_state</tt>.
   */
  behavior make_behavior() override {
    return static_cast<Derived*>(this)->init_state;
  }

 protected:

  template <class... Ts>
  sb_actor(Ts&&... args)
      : Base(std::forward<Ts>(args)...) {}

};

} // namespace caf

#endif // CAF_FSM_ACTOR_HPP
