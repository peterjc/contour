#pragma once

#include <vtbackend/primitives.h>

#include <vector>

namespace vtbackend
{

struct JumpHistory
{

    template <typename T>
    void add(T&& cell)
    {
        applyOffset();
        _history.push_back(std::forward<decltype(cell)>(cell));
    }
    CellLocation jumpToLast(CellLocation current);
    CellLocation jumpToMarkUp(CellLocation current);
    CellLocation jumpToMarkDown(CellLocation current);
    void addOffset(LineOffset offset) { _offsetSinceLastJump += offset; }

  private:
    std::vector<CellLocation> _history;
    size_t _current = 0;
    LineOffset _offsetSinceLastJump { 0 };
    void applyOffset()
    {
        if (unbox(_offsetSinceLastJump) == 0)
            return;
        for (auto& cell: _history)
        {
            // minus since we are going in the history
            cell.line -= _offsetSinceLastJump;
        }
        _offsetSinceLastJump = LineOffset { 0 };
    }
};
} // namespace vtbackend
