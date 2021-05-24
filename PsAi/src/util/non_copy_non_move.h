#pragma once

namespace PsAi::Util
{
	// Mixin class to make a subclass non-copyable and non-movable, deleting the move function and operator is
	// uneccessary but is here for the sake of being explicit.
	class NonCopyableNonMoveable
	{
		public:
			NonCopyableNonMoveable() = default;
			NonCopyableNonMoveable(const NonCopyableNonMoveable&) = delete;
			NonCopyableNonMoveable(NonCopyableNonMoveable&&) = delete;
			NonCopyableNonMoveable& operator=(const NonCopyableNonMoveable&) = delete;
			NonCopyableNonMoveable& operator=(NonCopyableNonMoveable&&) = delete;
	};

}
