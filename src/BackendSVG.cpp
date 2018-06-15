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

#include "BackendSVG.hpp"

namespace trase {

void BackendSVG::init(const char *filename, const char *name) {
  m_out.open(filename);

  out << R"del(
    <?xml version="1.0" standalone="no"?>
    <!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN" 
      "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd">
    )del";

  // out << "<svg width = \"" << width << "\" height=\"" << height << "\"";

  out << R"del(<svg version="1.1"
     xmlns="http://www.w3.org/2000/svg">
  <desc>)del"
      << name << "</desc>\n";
}

void BackendSVG::finalise() {
  out << "</svg>\n";
  out.close();
}

} // namespace trase

#include "DrawableDraw.hpp"

namespace trase {
template void Drawable::serialise<BackendSVG>(BackendSVG &backend);
} // namespace trase

#include "FigureDraw.hpp"

namespace trase {
template void Figure::draw<BackendGL>(BackendGL &backend, const float time);
template void Figure::show<BackendGL>(BackendGL &backend);
} // namespace trase

#include "AxisDraw.hpp"

namespace trase {
template void Axis::serialise<BackendSVG>(BackendSVG &backend);
template void Axis::draw_common<BackendSVG>(BackendSVG &backend);
} // namespace trase

#include "Plot1DDraw.hpp"

namespace trase {
template void Plot1D::serialise<BackendSVG>(BackendSVG &backend);
} // namespace trase