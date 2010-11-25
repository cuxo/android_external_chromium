// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/views/pinned_contents_info_bubble.h"

#include "chrome/browser/views/bubble_border.h"

void PinnedContentsBorderContents::SizeAndGetBounds(
    const gfx::Rect& position_relative_to,
    BubbleBorder::ArrowLocation arrow_location,
    bool allow_bubble_offscreen,
    const gfx::Size& contents_size,
    gfx::Rect* contents_bounds,
    gfx::Rect* window_bounds) {
  // Arrow offset is calculated from the middle of the |position_relative_to|.
  int offset = position_relative_to.x() + (position_relative_to.width() / 2);
  offset -= bubble_anchor_.x();

  gfx::Insets insets;
  bubble_border_->GetInsets(&insets);
  offset += kLeftMargin + insets.left() + 1;
  bubble_border_->SetArrowOffset(offset, contents_size);

  BorderContents::SizeAndGetBounds(
      position_relative_to, arrow_location,
      true,  // Don't move the bubble around if it does not fit on the screen.
      contents_size, contents_bounds, window_bounds);

  // Now move the y position to make sure the bubble contents overlap the view.
  window_bounds->Offset(0, -(kTopMargin + 1));
}

// InfoBubble -----------------------------------------------------------------

// static
PinnedContentsInfoBubble* PinnedContentsInfoBubble::Show(
    views::Widget* parent,
    const gfx::Rect& position_relative_to,
    BubbleBorder::ArrowLocation arrow_location,
    const gfx::Point& bubble_anchor,
    views::View* contents,
    InfoBubbleDelegate* delegate) {
  PinnedContentsInfoBubble* window =
      new PinnedContentsInfoBubble(bubble_anchor);
  window->Init(parent, position_relative_to, arrow_location,
               contents, delegate);
  return window;
}

BorderContents* PinnedContentsInfoBubble::CreateBorderContents() {
  return new PinnedContentsBorderContents(bubble_anchor_);
}