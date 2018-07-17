/*
Copyright (c) 2018, University of Oxford.
All rights reserved.

University of Oxford means the Chancellor, Masters and Scholars of the
University of Oxford, having an administrative office at Wellington
Square, Oxford OX1 2JD, UK.

This file is part of trase.

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

#include "util/Colors.hpp"

#include "util/Exception.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>

namespace trase {

RGBA::RGBA(int r, int g, int b, int a) noexcept
    : m_r(r), m_g(g), m_b(b), m_a(a) {}

RGBA::RGBA(const Vector<float, 4> &v) noexcept
    : m_r(static_cast<int>(v[0])), m_g(static_cast<int>(v[1])),
      m_b(static_cast<int>(v[2])), m_a(static_cast<int>(v[3])) {}

RGBA::RGBA(const Vector<float, 3> &v) noexcept
    : m_r(static_cast<int>(v[0])), m_g(static_cast<int>(v[1])),
      m_b(static_cast<int>(v[2])), m_a(255) {}

int RGBA::r() const noexcept { return m_r; }
int RGBA::g() const noexcept { return m_g; }
int RGBA::b() const noexcept { return m_b; }
int RGBA::a() const noexcept { return m_a; }

RGBA &RGBA::r(const int r) noexcept {
  m_r = r;
  return *this;
}

RGBA &RGBA::g(const int g) noexcept {
  m_g = g;
  return *this;
}

RGBA &RGBA::b(const int b) noexcept {
  m_b = b;
  return *this;
}

RGBA &RGBA::a(const int a) noexcept {
  m_a = a;
  return *this;
}

std::string RGBA::to_rgb_string() const noexcept {
  std::stringstream stream;
  stream.precision(2);

  stream << '#' << std::hex << std::setfill('0') << std::setw(2) << m_r
         << std::setw(2) << m_g << std::setw(2) << m_b;
  return stream.str();
}

bool RGBA::operator==(const RGBA &b) const noexcept {
  return m_r == b.r() && m_g == b.g() && m_b == b.b() && m_a == b.a();
}

bool RGBA::operator!=(const RGBA &b) const noexcept { return !(*this == b); }

const int RGBA::default_alpha = 200;

// default colors taken from d3 category10 color scheme
// https://github.com/d3/d3-3.x-api-reference/blob/master/Ordinal-Scales.md#category10
const std::array<const RGBA, 10> RGBA::defaults = {
    RGBA{31, 119, 180},  RGBA{255, 127, 14},  RGBA{44, 160, 44},
    RGBA{214, 39, 40},   RGBA{148, 103, 189}, RGBA{140, 86, 75},
    RGBA{227, 119, 194}, RGBA{127, 127, 127}, RGBA{188, 189, 34},
    RGBA{23, 190, 207}};

const RGBA RGBA::black{0, 0, 0};
const RGBA RGBA::white{255, 255, 255};

Colormap::Colormap(std::vector<Vector<float, 3>> list) noexcept
    : m_colors(std::move(list)) {}

RGBA Colormap::to_color(float i) const {
  if (i <= 0.f) {
    return RGBA(255.f * m_colors[0]);
  }
  if (i >= 1.f) {
    return RGBA(255.f * m_colors.back());
  }
  const float pos = i * m_colors.size();
  const auto c0 = m_colors[static_cast<int>(std::floor(pos))];
  const auto c1 = m_colors[static_cast<int>(std::ceil(pos))];

  return RGBA(255.f *
              ((pos - std::floor(pos)) * c1 + (std::ceil(pos) - pos) * c0));
}

/// https://github.com/BIDS/colormap/blob/master/option_d.py
const Colormap Colormaps::viridis(std::vector<Vector<float, 3>>{
    {{0.26700401f, 0.00487433f, 0.32941519f},
     {0.26851048f, 0.00960483f, 0.33542652f},
     {0.26994384f, 0.01462494f, 0.34137895f},
     {0.27130489f, 0.01994186f, 0.34726862f},
     {0.27259384f, 0.02556309f, 0.35309303f},
     {0.27380934f, 0.03149748f, 0.35885256f},
     {0.27495242f, 0.03775181f, 0.36454323f},
     {0.27602238f, 0.04416723f, 0.37016418f},
     {0.2770184f, 0.05034437f, 0.37571452f},
     {0.27794143f, 0.05632444f, 0.38119074f},
     {0.27879067f, 0.06214536f, 0.38659204f},
     {0.2795655f, 0.06783587f, 0.39191723f},
     {0.28026658f, 0.07341724f, 0.39716349f},
     {0.28089358f, 0.07890703f, 0.40232944f},
     {0.28144581f, 0.0843197f, 0.40741404f},
     {0.28192358f, 0.08966622f, 0.41241521f},
     {0.28232739f, 0.09495545f, 0.41733086f},
     {0.28265633f, 0.10019576f, 0.42216032f},
     {0.28291049f, 0.10539345f, 0.42690202f},
     {0.28309095f, 0.11055307f, 0.43155375f},
     {0.28319704f, 0.11567966f, 0.43611482f},
     {0.28322882f, 0.12077701f, 0.44058404f},
     {0.28318684f, 0.12584799f, 0.44496f},
     {0.283072f, 0.13089477f, 0.44924127f},
     {0.28288389f, 0.13592005f, 0.45342734f},
     {0.28262297f, 0.14092556f, 0.45751726f},
     {0.28229037f, 0.14591233f, 0.46150995f},
     {0.28188676f, 0.15088147f, 0.46540474f},
     {0.28141228f, 0.15583425f, 0.46920128f},
     {0.28086773f, 0.16077132f, 0.47289909f},
     {0.28025468f, 0.16569272f, 0.47649762f},
     {0.27957399f, 0.17059884f, 0.47999675f},
     {0.27882618f, 0.1754902f, 0.48339654f},
     {0.27801236f, 0.18036684f, 0.48669702f},
     {0.27713437f, 0.18522836f, 0.48989831f},
     {0.27619376f, 0.19007447f, 0.49300074f},
     {0.27519116f, 0.1949054f, 0.49600488f},
     {0.27412802f, 0.19972086f, 0.49891131f},
     {0.27300596f, 0.20452049f, 0.50172076f},
     {0.27182812f, 0.20930306f, 0.50443413f},
     {0.27059473f, 0.21406899f, 0.50705243f},
     {0.26930756f, 0.21881782f, 0.50957678f},
     {0.26796846f, 0.22354911f, 0.5120084f},
     {0.26657984f, 0.2282621f, 0.5143487f},
     {0.2651445f, 0.23295593f, 0.5165993f},
     {0.2636632f, 0.23763078f, 0.51876163f},
     {0.26213801f, 0.24228619f, 0.52083736f},
     {0.26057103f, 0.2469217f, 0.52282822f},
     {0.25896451f, 0.25153685f, 0.52473609f},
     {0.25732244f, 0.2561304f, 0.52656332f},
     {0.25564519f, 0.26070284f, 0.52831152f},
     {0.25393498f, 0.26525384f, 0.52998273f},
     {0.25219404f, 0.26978306f, 0.53157905f},
     {0.25042462f, 0.27429024f, 0.53310261f},
     {0.24862899f, 0.27877509f, 0.53455561f},
     {0.2468114f, 0.28323662f, 0.53594093f},
     {0.24497208f, 0.28767547f, 0.53726018f},
     {0.24311324f, 0.29209154f, 0.53851561f},
     {0.24123708f, 0.29648471f, 0.53970946f},
     {0.23934575f, 0.30085494f, 0.54084398f},
     {0.23744138f, 0.30520222f, 0.5419214f},
     {0.23552606f, 0.30952657f, 0.54294396f},
     {0.23360277f, 0.31382773f, 0.54391424f},
     {0.2316735f, 0.3181058f, 0.54483444f},
     {0.22973926f, 0.32236127f, 0.54570633f},
     {0.22780192f, 0.32659432f, 0.546532f},
     {0.2258633f, 0.33080515f, 0.54731353f},
     {0.22392515f, 0.334994f, 0.54805291f},
     {0.22198915f, 0.33916114f, 0.54875211f},
     {0.22005691f, 0.34330688f, 0.54941304f},
     {0.21812995f, 0.34743154f, 0.55003755f},
     {0.21620971f, 0.35153548f, 0.55062743f},
     {0.21429757f, 0.35561907f, 0.5511844f},
     {0.21239477f, 0.35968273f, 0.55171011f},
     {0.2105031f, 0.36372671f, 0.55220646f},
     {0.20862342f, 0.36775151f, 0.55267486f},
     {0.20675628f, 0.37175775f, 0.55311653f},
     {0.20490257f, 0.37574589f, 0.55353282f},
     {0.20306309f, 0.37971644f, 0.55392505f},
     {0.20123854f, 0.38366989f, 0.55429441f},
     {0.1994295f, 0.38760678f, 0.55464205f},
     {0.1976365f, 0.39152762f, 0.55496905f},
     {0.19585993f, 0.39543297f, 0.55527637f},
     {0.19410009f, 0.39932336f, 0.55556494f},
     {0.19235719f, 0.40319934f, 0.55583559f},
     {0.19063135f, 0.40706148f, 0.55608907f},
     {0.18892259f, 0.41091033f, 0.55632606f},
     {0.18723083f, 0.41474645f, 0.55654717f},
     {0.18555593f, 0.4185704f, 0.55675292f},
     {0.18389763f, 0.42238275f, 0.55694377f},
     {0.18225561f, 0.42618405f, 0.5571201f},
     {0.18062949f, 0.42997486f, 0.55728221f},
     {0.17901879f, 0.43375572f, 0.55743035f},
     {0.17742298f, 0.4375272f, 0.55756466f},
     {0.17584148f, 0.44128981f, 0.55768526f},
     {0.17427363f, 0.4450441f, 0.55779216f},
     {0.17271876f, 0.4487906f, 0.55788532f},
     {0.17117615f, 0.4525298f, 0.55796464f},
     {0.16964573f, 0.45626209f, 0.55803034f},
     {0.16812641f, 0.45998802f, 0.55808199f},
     {0.1666171f, 0.46370813f, 0.55811913f},
     {0.16511703f, 0.4674229f, 0.55814141f},
     {0.16362543f, 0.47113278f, 0.55814842f},
     {0.16214155f, 0.47483821f, 0.55813967f},
     {0.16066467f, 0.47853961f, 0.55811466f},
     {0.15919413f, 0.4822374f, 0.5580728f},
     {0.15772933f, 0.48593197f, 0.55801347f},
     {0.15626973f, 0.4896237f, 0.557936f},
     {0.15481488f, 0.49331293f, 0.55783967f},
     {0.15336445f, 0.49700003f, 0.55772371f},
     {0.1519182f, 0.50068529f, 0.55758733f},
     {0.15047605f, 0.50436904f, 0.55742968f},
     {0.14903918f, 0.50805136f, 0.5572505f},
     {0.14760731f, 0.51173263f, 0.55704861f},
     {0.14618026f, 0.51541316f, 0.55682271f},
     {0.14475863f, 0.51909319f, 0.55657181f},
     {0.14334327f, 0.52277292f, 0.55629491f},
     {0.14193527f, 0.52645254f, 0.55599097f},
     {0.14053599f, 0.53013219f, 0.55565893f},
     {0.13914708f, 0.53381201f, 0.55529773f},
     {0.13777048f, 0.53749213f, 0.55490625f},
     {0.1364085f, 0.54117264f, 0.55448339f},
     {0.13506561f, 0.54485335f, 0.55402906f},
     {0.13374299f, 0.54853458f, 0.55354108f},
     {0.13244401f, 0.55221637f, 0.55301828f},
     {0.13117249f, 0.55589872f, 0.55245948f},
     {0.1299327f, 0.55958162f, 0.55186354f},
     {0.12872938f, 0.56326503f, 0.55122927f},
     {0.12756771f, 0.56694891f, 0.55055551f},
     {0.12645338f, 0.57063316f, 0.5498411f},
     {0.12539383f, 0.57431754f, 0.54908564f},
     {0.12439474f, 0.57800205f, 0.5482874f},
     {0.12346281f, 0.58168661f, 0.54744498f},
     {0.12260562f, 0.58537105f, 0.54655722f},
     {0.12183122f, 0.58905521f, 0.54562298f},
     {0.12114807f, 0.59273889f, 0.54464114f},
     {0.12056501f, 0.59642187f, 0.54361058f},
     {0.12009154f, 0.60010387f, 0.54253043f},
     {0.11973756f, 0.60378459f, 0.54139999f},
     {0.11951163f, 0.60746388f, 0.54021751f},
     {0.11942341f, 0.61114146f, 0.53898192f},
     {0.11948255f, 0.61481702f, 0.53769219f},
     {0.11969858f, 0.61849025f, 0.53634733f},
     {0.12008079f, 0.62216081f, 0.53494633f},
     {0.12063824f, 0.62582833f, 0.53348834f},
     {0.12137972f, 0.62949242f, 0.53197275f},
     {0.12231244f, 0.63315277f, 0.53039808f},
     {0.12344358f, 0.63680899f, 0.52876343f},
     {0.12477953f, 0.64046069f, 0.52706792f},
     {0.12632581f, 0.64410744f, 0.52531069f},
     {0.12808703f, 0.64774881f, 0.52349092f},
     {0.13006688f, 0.65138436f, 0.52160791f},
     {0.13226797f, 0.65501363f, 0.51966086f},
     {0.13469183f, 0.65863619f, 0.5176488f},
     {0.13733921f, 0.66225157f, 0.51557101f},
     {0.14020991f, 0.66585927f, 0.5134268f},
     {0.14330291f, 0.66945881f, 0.51121549f},
     {0.1466164f, 0.67304968f, 0.50893644f},
     {0.15014782f, 0.67663139f, 0.5065889f},
     {0.15389405f, 0.68020343f, 0.50417217f},
     {0.15785146f, 0.68376525f, 0.50168574f},
     {0.16201598f, 0.68731632f, 0.49912906f},
     {0.1663832f, 0.69085611f, 0.49650163f},
     {0.1709484f, 0.69438405f, 0.49380294f},
     {0.17570671f, 0.6978996f, 0.49103252f},
     {0.18065314f, 0.70140222f, 0.48818938f},
     {0.18578266f, 0.70489133f, 0.48527326f},
     {0.19109018f, 0.70836635f, 0.48228395f},
     {0.19657063f, 0.71182668f, 0.47922108f},
     {0.20221902f, 0.71527175f, 0.47608431f},
     {0.20803045f, 0.71870095f, 0.4728733f},
     {0.21400015f, 0.72211371f, 0.46958774f},
     {0.22012381f, 0.72550945f, 0.46622638f},
     {0.2263969f, 0.72888753f, 0.46278934f},
     {0.23281498f, 0.73224735f, 0.45927675f},
     {0.2393739f, 0.73558828f, 0.45568838f},
     {0.24606968f, 0.73890972f, 0.45202405f},
     {0.25289851f, 0.74221104f, 0.44828355f},
     {0.25985676f, 0.74549162f, 0.44446673f},
     {0.26694127f, 0.74875084f, 0.44057284f},
     {0.27414922f, 0.75198807f, 0.4366009f},
     {0.28147681f, 0.75520266f, 0.43255207f},
     {0.28892102f, 0.75839399f, 0.42842626f},
     {0.29647899f, 0.76156142f, 0.42422341f},
     {0.30414796f, 0.76470433f, 0.41994346f},
     {0.31192534f, 0.76782207f, 0.41558638f},
     {0.3198086f, 0.77091403f, 0.41115215f},
     {0.3277958f, 0.77397953f, 0.40664011f},
     {0.33588539f, 0.7770179f, 0.40204917f},
     {0.34407411f, 0.78002855f, 0.39738103f},
     {0.35235985f, 0.78301086f, 0.39263579f},
     {0.36074053f, 0.78596419f, 0.38781353f},
     {0.3692142f, 0.78888793f, 0.38291438f},
     {0.37777892f, 0.79178146f, 0.3779385f},
     {0.38643282f, 0.79464415f, 0.37288606f},
     {0.39517408f, 0.79747541f, 0.36775726f},
     {0.40400101f, 0.80027461f, 0.36255223f},
     {0.4129135f, 0.80304099f, 0.35726893f},
     {0.42190813f, 0.80577412f, 0.35191009f},
     {0.43098317f, 0.80847343f, 0.34647607f},
     {0.44013691f, 0.81113836f, 0.3409673f},
     {0.44936763f, 0.81376835f, 0.33538426f},
     {0.45867362f, 0.81636288f, 0.32972749f},
     {0.46805314f, 0.81892143f, 0.32399761f},
     {0.47750446f, 0.82144351f, 0.31819529f},
     {0.4870258f, 0.82392862f, 0.31232133f},
     {0.49661536f, 0.82637633f, 0.30637661f},
     {0.5062713f, 0.82878621f, 0.30036211f},
     {0.51599182f, 0.83115784f, 0.29427888f},
     {0.52577622f, 0.83349064f, 0.2881265f},
     {0.5356211f, 0.83578452f, 0.28190832f},
     {0.5455244f, 0.83803918f, 0.27562602f},
     {0.55548397f, 0.84025437f, 0.26928147f},
     {0.5654976f, 0.8424299f, 0.26287683f},
     {0.57556297f, 0.84456561f, 0.25641457f},
     {0.58567772f, 0.84666139f, 0.24989748f},
     {0.59583934f, 0.84871722f, 0.24332878f},
     {0.60604528f, 0.8507331f, 0.23671214f},
     {0.61629283f, 0.85270912f, 0.23005179f},
     {0.62657923f, 0.85464543f, 0.22335258f},
     {0.63690157f, 0.85654226f, 0.21662012f},
     {0.64725685f, 0.85839991f, 0.20986086f},
     {0.65764197f, 0.86021878f, 0.20308229f},
     {0.66805369f, 0.86199932f, 0.19629307f},
     {0.67848868f, 0.86374211f, 0.18950326f},
     {0.68894351f, 0.86544779f, 0.18272455f},
     {0.69941463f, 0.86711711f, 0.17597055f},
     {0.70989842f, 0.86875092f, 0.16925712f},
     {0.72039115f, 0.87035015f, 0.16260273f},
     {0.73088902f, 0.87191584f, 0.15602894f},
     {0.74138803f, 0.87344918f, 0.14956101f},
     {0.75188414f, 0.87495143f, 0.14322828f},
     {0.76237342f, 0.87642392f, 0.13706449f},
     {0.77285183f, 0.87786808f, 0.13110864f},
     {0.78331535f, 0.87928545f, 0.12540538f},
     {0.79375994f, 0.88067763f, 0.12000532f},
     {0.80418159f, 0.88204632f, 0.11496505f},
     {0.81457634f, 0.88339329f, 0.11034678f},
     {0.82494028f, 0.88472036f, 0.10621724f},
     {0.83526959f, 0.88602943f, 0.1026459f},
     {0.84556056f, 0.88732243f, 0.09970219f},
     {0.8558096f, 0.88860134f, 0.09745186f},
     {0.86601325f, 0.88986815f, 0.09595277f},
     {0.87616824f, 0.89112487f, 0.09525046f},
     {0.88627146f, 0.89237353f, 0.09537439f},
     {0.89632002f, 0.89361614f, 0.09633538f},
     {0.90631121f, 0.89485467f, 0.09812496f},
     {0.91624212f, 0.89609127f, 0.1007168f},
     {0.92610579f, 0.89732977f, 0.10407067f},
     {0.93590444f, 0.8985704f, 0.10813094f},
     {0.94563626f, 0.899815f, 0.11283773f},
     {0.95529972f, 0.90106534f, 0.11812832f},
     {0.96489353f, 0.90232311f, 0.12394051f},
     {0.97441665f, 0.90358991f, 0.13021494f},
     {0.98386829f, 0.90486726f, 0.13689671f},
     {0.99324789f, 0.90615657f, 0.1439362f}}});

} // namespace trase