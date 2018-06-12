/*
Copyright (c) 2018, University of Oxford.
All rights reserved.

University of Oxford means the Chancellor, Masters and Scholars of the
University of Oxford, having an administrative office at Wellington
Square, Oxford OX1 2JD, UK.

This file is part of the Oxford RSE C++ Template project.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "Figure.hpp"
#include <array>
#include <string>

namespace trase {

template <typename Backend> void Figure::show(Backend &backend) {
  auto name = "Figure " + std::to_string(m_id);
  backend.init(this->m_pixels.bmax[0], this->m_pixels.bmax[1], name.c_str());

  // Main loop
  while (!backend.should_close()) {
    const vfloat2_t win_limits = backend.begin_frame();
    if ((win_limits != m_pixels.bmax).any()) {
      m_pixels.bmax = win_limits;
      m_axis->resize(m_pixels);
    }

    if (backend.is_interactive()) {
      if (backend.mouse_dragging()) {
        vfloat2_t delta = backend.mouse_drag_delta();

        // scale by axis pixel area
        delta /= m_axis->pixels().bmax * vfloat2_t(-1, 1);

        // scale by axis limits
        delta *= m_axis->limits().delta();

        m_axis->limits() += delta;
        backend.mouse_drag_reset_delta();
      }
    }

    draw(backend);
    backend.end_frame();
  }
  backend.finalise();
}

template <typename Backend> void Figure::draw(Backend &backend) {
  m_axis->draw(backend);
}

} // namespace trase