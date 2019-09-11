#ifndef HEADER_IPV4_PROTOCOL_H_
#define HEADER_IPV4_PROTOCOL_H_

#include <cstdint>

namespace header
{
namespace ipv4
{

enum class Protocol : std::uint8_t
{
    hopopt = 0,
    icmp = 1,
    igmp = 2,
    ggp = 3,
    ipv4 = 4,
    st = 5,
    tcp = 6,
    cbt = 7,
    egp = 8,
    igp = 9,
    bbn_rcc_mon = 10,
    nvp_ii = 11,
    pup = 12,
    argus = 13, //deprecated
    emcon = 14,
    xnet = 15,
    chaos = 16,
    udp = 17,
    mux = 18,
    dcn_meas = 19,
    hmp = 20,
    prm = 21,
    xns_idp = 22,
    trunk_1 = 23,
    truck_2 = 24,
    leaf_1 = 25,
    leaf_2 = 26,
    rdp = 27,
    irtp = 28,
    iso_tp4 = 29,
    netblt = 30,
    mfe_nsp = 31,
    merit_inp = 32,
    dccp = 33,
    _3pc = 34,
    idpr = 35,
    xtp = 36,
    ddp = 37,
    idpr_cmtp = 38,
    tp_plus_plus = 39,
    il = 40,
    ipv6 = 41,
    sdrp = 42,
    ipv6_route = 43,
    ipv6_frag = 44,
    idrp = 45,
    rsvp = 46,
    gre = 47,
    dsr = 48,
    bna = 49,
    esp = 50,
    ah = 51,
    i_nlsp = 52,
    swipe = 53, //deprecated
    narp = 54,
    mobile = 55,
    tlsp = 56,
    skip = 57,
    ipv6_icmp = 58,
    ipv6_nonxt = 59,
    ipv6_opts = 60,
    any_host_internal_protocol = 61,
    cftp = 62,
    any_local_network = 63,
    sat_expak = 64,
    kryptolan = 65,
    rvd = 66,
    ippc = 67,
    any_distributed_file_system = 68,
    sat_mon = 69,
    visa = 70,
    ipcv = 71,
    cpnx = 72,
    cphb = 73,
    wsn = 74,
    pvp = 75,
    br_sat_mon = 76,
    sun_nd = 77,
    wb_mon = 78,
    wb_expak = 79,
    iso_ip = 80,
    vmtp = 81,
    secure_vmtp = 82,
    vines = 83,
    tpp_or_iptm = 84,
    tpp = 84,
    iptm = 84,
    nsfnet_igp = 85,
    dgp = 86,
    tcf = 87,
    eigrp = 88,
    ospfigp = 89,
    sprite_rpc = 90,
    larp = 91,
    mtp = 92,
    ax_dot_25 = 93,
    ipip = 94,
    micp = 95, //deprecated,
    scc_sp = 96,
    etherip = 97,
    encap = 98,
    any_private_encryption_scheme = 99,
    gmtp = 100,
    ifmp = 101,
    pnni = 102,
    pim = 103,
    aris = 104,
    scps = 105,
    qnx = 106,
    a_slash_n = 107,
    ipcomp = 108,
    snp = 109,
    compaq_peer = 110,
    ipx_in_ip = 111,
    vrrp = 112,
    pgm = 113,
    any_0_hop_protocol = 114,
    l2tp = 115,
    ddx = 116,
    iatp = 117,
    stp = 118,
    srp = 119,
    uti = 120,
    smp = 121,
    sm = 122, //deprecated
    ptp = 123,
    isis_over_ipv4 = 124,
    fire = 125,
    crtp = 126,
    crudp = 127,
    sscopmce = 128,
    ipcl = 129,
    sps = 130,
    pipe = 131,
    sctp = 132,
    fc = 133,
    rsvp_e2e_ignore = 134,
    mobility_header = 135,
    udplite = 136,
    mpls_in_ip = 137,
    manet = 138,
    hip = 139,
    shim6 = 140,
    wesp = 141,
    rohc = 142,
    unassigned_143 = 143,
    unassigned_144 = 144,
    unassigned_145 = 145,
    unassigned_146 = 146,
    unassigned_147 = 147,
    unassigned_148 = 148,
    unassigned_149 = 149,
    unassigned_150 = 150,
    unassigned_151 = 151,
    unassigned_152 = 152,
    unassigned_153 = 153,
    unassigned_154 = 154,
    unassigned_155 = 155,
    unassigned_156 = 156,
    unassigned_157 = 157,
    unassigned_158 = 158,
    unassigned_159 = 159,
    unassigned_160 = 160,
    unassigned_161 = 161,
    unassigned_162 = 162,
    unassigned_163 = 163,
    unassigned_164 = 164,
    unassigned_165 = 165,
    unassigned_166 = 166,
    unassigned_167 = 167,
    unassigned_168 = 168,
    unassigned_169 = 169,
    unassigned_170 = 170,
    unassigned_171 = 171,
    unassigned_172 = 172,
    unassigned_173 = 173,
    unassigned_174 = 174,
    unassigned_175 = 175,
    unassigned_176 = 176,
    unassigned_177 = 177,
    unassigned_178 = 178,
    unassigned_179 = 179,
    unassigned_180 = 180,
    unassigned_181 = 181,
    unassigned_182 = 182,
    unassigned_183 = 183,
    unassigned_184 = 184,
    unassigned_185 = 185,
    unassigned_186 = 186,
    unassigned_187 = 187,
    unassigned_188 = 188,
    unassigned_189 = 189,
    unassigned_190 = 190,
    unassigned_191 = 191,
    unassigned_192 = 192,
    unassigned_193 = 193,
    unassigned_194 = 194,
    unassigned_195 = 195,
    unassigned_196 = 196,
    unassigned_197 = 197,
    unassigned_198 = 198,
    unassigned_199 = 199,
    unassigned_200 = 200,
    unassigned_201 = 201,
    unassigned_202 = 202,
    unassigned_203 = 203,
    unassigned_204 = 204,
    unassigned_205 = 205,
    unassigned_206 = 206,
    unassigned_207 = 207,
    unassigned_208 = 208,
    unassigned_209 = 209,
    unassigned_210 = 210,
    unassigned_211 = 211,
    unassigned_212 = 212,
    unassigned_213 = 213,
    unassigned_214 = 214,
    unassigned_215 = 215,
    unassigned_216 = 216,
    unassigned_217 = 217,
    unassigned_218 = 218,
    unassigned_219 = 219,
    unassigned_220 = 220,
    unassigned_221 = 221,
    unassigned_222 = 222,
    unassigned_223 = 223,
    unassigned_224 = 224,
    unassigned_225 = 225,
    unassigned_226 = 226,
    unassigned_227 = 227,
    unassigned_228 = 228,
    unassigned_229 = 229,
    unassigned_230 = 230,
    unassigned_231 = 231,
    unassigned_232 = 232,
    unassigned_233 = 233,
    unassigned_234 = 234,
    unassigned_235 = 235,
    unassigned_236 = 236,
    unassigned_237 = 237,
    unassigned_238 = 238,
    unassigned_239 = 239,
    unassigned_240 = 240,
    unassigned_241 = 241,
    unassigned_242 = 242,
    unassigned_243 = 243,
    unassigned_244 = 244,
    unassigned_245 = 245,
    unassigned_246 = 246,
    unassigned_247 = 247,
    unassigned_248 = 248,
    unassigned_249 = 249,
    unassigned_250 = 250,
    unassigned_251 = 251,
    unassigned_252 = 252,
    use_for_experimentation_and_testing_1 = 253,
    use_for_experimentation_and_testing_2 = 254,
    reserved = 255
};

namespace protocol
{

inline constexpr std::uint8_t 
    ToValue(const header::ipv4::Protocol & protocol_enum)
{
    return static_cast<std::uint8_t >(protocol_enum);
}

inline header::ipv4::Protocol ToEnum(const std::uint8_t & protocol_value)
{
    switch(protocol_value)
    {
        case ToValue(header::ipv4::Protocol::hopopt) :
            return header::ipv4::Protocol::hopopt;
        case ToValue(header::ipv4::Protocol::icmp) :
            return header::ipv4::Protocol::icmp;
        case ToValue(header::ipv4::Protocol::igmp) :
            return header::ipv4::Protocol::igmp;
        case ToValue(header::ipv4::Protocol::ggp) :
            return header::ipv4::Protocol::ggp;
        case ToValue(header::ipv4::Protocol::ipv4) :
            return header::ipv4::Protocol::ipv4;
        case ToValue(header::ipv4::Protocol::st) :
            return header::ipv4::Protocol::st;
        case ToValue(header::ipv4::Protocol::tcp) :
            return header::ipv4::Protocol::tcp;
        case ToValue(header::ipv4::Protocol::cbt) :
            return header::ipv4::Protocol::cbt;
        case ToValue(header::ipv4::Protocol::egp) :
            return header::ipv4::Protocol::egp;
        case ToValue(header::ipv4::Protocol::igp) :
            return header::ipv4::Protocol::igp;
        case ToValue(header::ipv4::Protocol::bbn_rcc_mon) :
            return header::ipv4::Protocol::bbn_rcc_mon;
        case ToValue(header::ipv4::Protocol::nvp_ii) :
            return header::ipv4::Protocol::nvp_ii;
        case ToValue(header::ipv4::Protocol::pup) :
            return header::ipv4::Protocol::pup;
        case ToValue(header::ipv4::Protocol::argus) :
            return header::ipv4::Protocol::argus;
        case ToValue(header::ipv4::Protocol::emcon) :
            return header::ipv4::Protocol::emcon;
        case ToValue(header::ipv4::Protocol::xnet) :
            return header::ipv4::Protocol::xnet;
        case ToValue(header::ipv4::Protocol::chaos) :
            return header::ipv4::Protocol::chaos;
        case ToValue(header::ipv4::Protocol::udp) :
            return header::ipv4::Protocol::udp;
        case ToValue(header::ipv4::Protocol::mux) :
            return header::ipv4::Protocol::mux;
        case ToValue(header::ipv4::Protocol::dcn_meas) :
            return header::ipv4::Protocol::dcn_meas;
        case ToValue(header::ipv4::Protocol::hmp) :
            return header::ipv4::Protocol::hmp;
        case ToValue(header::ipv4::Protocol::prm) :
            return header::ipv4::Protocol::prm;
        case ToValue(header::ipv4::Protocol::xns_idp) :
            return header::ipv4::Protocol::xns_idp;
        case ToValue(header::ipv4::Protocol::trunk_1) :
            return header::ipv4::Protocol::trunk_1;
        case ToValue(header::ipv4::Protocol::truck_2) :
            return header::ipv4::Protocol::truck_2;
        case ToValue(header::ipv4::Protocol::leaf_1) :
            return header::ipv4::Protocol::leaf_1;
        case ToValue(header::ipv4::Protocol::leaf_2) :
            return header::ipv4::Protocol::leaf_2;
        case ToValue(header::ipv4::Protocol::rdp) :
            return header::ipv4::Protocol::rdp;
        case ToValue(header::ipv4::Protocol::irtp) :
            return header::ipv4::Protocol::irtp;
        case ToValue(header::ipv4::Protocol::iso_tp4) :
            return header::ipv4::Protocol::iso_tp4;
        case ToValue(header::ipv4::Protocol::netblt) :
            return header::ipv4::Protocol::netblt;
        case ToValue(header::ipv4::Protocol::mfe_nsp) :
            return header::ipv4::Protocol::mfe_nsp;
        case ToValue(header::ipv4::Protocol::merit_inp) :
            return header::ipv4::Protocol::merit_inp;
        case ToValue(header::ipv4::Protocol::dccp) :
            return header::ipv4::Protocol::dccp;
        case ToValue(header::ipv4::Protocol::_3pc) :
            return header::ipv4::Protocol::_3pc;
        case ToValue(header::ipv4::Protocol::idpr) :
            return header::ipv4::Protocol::idpr;
        case ToValue(header::ipv4::Protocol::xtp) :
            return header::ipv4::Protocol::xtp;
        case ToValue(header::ipv4::Protocol::ddp) :
            return header::ipv4::Protocol::ddp;
        case ToValue(header::ipv4::Protocol::idpr_cmtp) :
            return header::ipv4::Protocol::idpr_cmtp;
        case ToValue(header::ipv4::Protocol::tp_plus_plus) :
            return header::ipv4::Protocol::tp_plus_plus;
        case ToValue(header::ipv4::Protocol::il) :
            return header::ipv4::Protocol::il;
        case ToValue(header::ipv4::Protocol::ipv6) :
            return header::ipv4::Protocol::ipv6;
        case ToValue(header::ipv4::Protocol::sdrp) :
            return header::ipv4::Protocol::sdrp;
        case ToValue(header::ipv4::Protocol::ipv6_route) :
            return header::ipv4::Protocol::ipv6_route;
        case ToValue(header::ipv4::Protocol::ipv6_frag) :
            return header::ipv4::Protocol::ipv6_frag;
        case ToValue(header::ipv4::Protocol::idrp) :
            return header::ipv4::Protocol::idrp;
        case ToValue(header::ipv4::Protocol::rsvp) :
            return header::ipv4::Protocol::rsvp;
        case ToValue(header::ipv4::Protocol::gre) :
            return header::ipv4::Protocol::gre;
        case ToValue(header::ipv4::Protocol::dsr) :
            return header::ipv4::Protocol::dsr;
        case ToValue(header::ipv4::Protocol::bna) :
            return header::ipv4::Protocol::bna;
        case ToValue(header::ipv4::Protocol::esp) :
            return header::ipv4::Protocol::esp;
        case ToValue(header::ipv4::Protocol::ah) :
            return header::ipv4::Protocol::ah;
        case ToValue(header::ipv4::Protocol::i_nlsp) :
            return header::ipv4::Protocol::i_nlsp;
        case ToValue(header::ipv4::Protocol::swipe) :
            return header::ipv4::Protocol::swipe;
        case ToValue(header::ipv4::Protocol::narp) :
            return header::ipv4::Protocol::narp;
        case ToValue(header::ipv4::Protocol::mobile) :
            return header::ipv4::Protocol::mobile;
        case ToValue(header::ipv4::Protocol::tlsp) :
            return header::ipv4::Protocol::tlsp;
        case ToValue(header::ipv4::Protocol::skip) :
            return header::ipv4::Protocol::skip;
        case ToValue(header::ipv4::Protocol::ipv6_icmp) :
            return header::ipv4::Protocol::ipv6_icmp;
        case ToValue(header::ipv4::Protocol::ipv6_nonxt) :
            return header::ipv4::Protocol::ipv6_nonxt;
        case ToValue(header::ipv4::Protocol::ipv6_opts) :
            return header::ipv4::Protocol::ipv6_opts;
        case ToValue(header::ipv4::Protocol::any_host_internal_protocol) :
            return header::ipv4::Protocol::any_host_internal_protocol;
        case ToValue(header::ipv4::Protocol::cftp) :
            return header::ipv4::Protocol::cftp;
        case ToValue(header::ipv4::Protocol::any_local_network) :
            return header::ipv4::Protocol::any_local_network;
        case ToValue(header::ipv4::Protocol::sat_expak) :
            return header::ipv4::Protocol::sat_expak;
        case ToValue(header::ipv4::Protocol::kryptolan) :
            return header::ipv4::Protocol::kryptolan;
        case ToValue(header::ipv4::Protocol::rvd) :
            return header::ipv4::Protocol::rvd;
        case ToValue(header::ipv4::Protocol::ippc) :
            return header::ipv4::Protocol::ippc;
        case ToValue(header::ipv4::Protocol::any_distributed_file_system) :
            return header::ipv4::Protocol::any_distributed_file_system;
        case ToValue(header::ipv4::Protocol::sat_mon) :
            return header::ipv4::Protocol::sat_mon;
        case ToValue(header::ipv4::Protocol::visa) :
            return header::ipv4::Protocol::visa;
        case ToValue(header::ipv4::Protocol::ipcv) :
            return header::ipv4::Protocol::ipcv;
        case ToValue(header::ipv4::Protocol::cpnx) :
            return header::ipv4::Protocol::cpnx;
        case ToValue(header::ipv4::Protocol::cphb) :
            return header::ipv4::Protocol::cphb;
        case ToValue(header::ipv4::Protocol::wsn) :
            return header::ipv4::Protocol::wsn;
        case ToValue(header::ipv4::Protocol::pvp) :
            return header::ipv4::Protocol::pvp;
        case ToValue(header::ipv4::Protocol::br_sat_mon) :
            return header::ipv4::Protocol::br_sat_mon;
        case ToValue(header::ipv4::Protocol::sun_nd) :
            return header::ipv4::Protocol::sun_nd;
        case ToValue(header::ipv4::Protocol::wb_mon) :
            return header::ipv4::Protocol::wb_mon;
        case ToValue(header::ipv4::Protocol::wb_expak) :
            return header::ipv4::Protocol::wb_expak;
        case ToValue(header::ipv4::Protocol::iso_ip) :
            return header::ipv4::Protocol::iso_ip;
        case ToValue(header::ipv4::Protocol::vmtp) :
            return header::ipv4::Protocol::vmtp;
        case ToValue(header::ipv4::Protocol::secure_vmtp) :
            return header::ipv4::Protocol::secure_vmtp;
        case ToValue(header::ipv4::Protocol::vines) :
            return header::ipv4::Protocol::vines;
        case ToValue(header::ipv4::Protocol::tpp_or_iptm) :
            return header::ipv4::Protocol::tpp_or_iptm;
        case ToValue(header::ipv4::Protocol::nsfnet_igp) :
            return header::ipv4::Protocol::nsfnet_igp;
        case ToValue(header::ipv4::Protocol::dgp) :
            return header::ipv4::Protocol::dgp;
        case ToValue(header::ipv4::Protocol::tcf) :
            return header::ipv4::Protocol::tcf;
        case ToValue(header::ipv4::Protocol::eigrp) :
            return header::ipv4::Protocol::eigrp;
        case ToValue(header::ipv4::Protocol::ospfigp) :
            return header::ipv4::Protocol::ospfigp;
        case ToValue(header::ipv4::Protocol::sprite_rpc) :
            return header::ipv4::Protocol::sprite_rpc;
        case ToValue(header::ipv4::Protocol::larp) :
            return header::ipv4::Protocol::larp;
        case ToValue(header::ipv4::Protocol::mtp) :
            return header::ipv4::Protocol::mtp;
        case ToValue(header::ipv4::Protocol::ax_dot_25) :
            return header::ipv4::Protocol::ax_dot_25;
        case ToValue(header::ipv4::Protocol::ipip) :
            return header::ipv4::Protocol::ipip;
        case ToValue(header::ipv4::Protocol::micp) :
            return header::ipv4::Protocol::micp;
        case ToValue(header::ipv4::Protocol::scc_sp) :
            return header::ipv4::Protocol::scc_sp;
        case ToValue(header::ipv4::Protocol::etherip) :
            return header::ipv4::Protocol::etherip;
        case ToValue(header::ipv4::Protocol::encap) :
            return header::ipv4::Protocol::encap;
        case ToValue(header::ipv4::Protocol::any_private_encryption_scheme) :
            return header::ipv4::Protocol::any_private_encryption_scheme;
        case ToValue(header::ipv4::Protocol::gmtp) :
            return header::ipv4::Protocol::gmtp;
        case ToValue(header::ipv4::Protocol::ifmp) :
            return header::ipv4::Protocol::ifmp;
        case ToValue(header::ipv4::Protocol::pnni) :
            return header::ipv4::Protocol::pnni;
        case ToValue(header::ipv4::Protocol::pim) :
            return header::ipv4::Protocol::pim;
        case ToValue(header::ipv4::Protocol::aris) :
            return header::ipv4::Protocol::aris;
        case ToValue(header::ipv4::Protocol::scps) :
            return header::ipv4::Protocol::scps;
        case ToValue(header::ipv4::Protocol::qnx) :
            return header::ipv4::Protocol::qnx;
        case ToValue(header::ipv4::Protocol::a_slash_n) :
            return header::ipv4::Protocol::a_slash_n;
        case ToValue(header::ipv4::Protocol::ipcomp) :
            return header::ipv4::Protocol::ipcomp;
        case ToValue(header::ipv4::Protocol::snp) :
            return header::ipv4::Protocol::snp;
        case ToValue(header::ipv4::Protocol::compaq_peer) :
            return header::ipv4::Protocol::compaq_peer;
        case ToValue(header::ipv4::Protocol::ipx_in_ip) :
            return header::ipv4::Protocol::ipx_in_ip;
        case ToValue(header::ipv4::Protocol::vrrp) :
            return header::ipv4::Protocol::vrrp;
        case ToValue(header::ipv4::Protocol::pgm) :
            return header::ipv4::Protocol::pgm;
        case ToValue(header::ipv4::Protocol::any_0_hop_protocol) :
            return header::ipv4::Protocol::any_0_hop_protocol;
        case ToValue(header::ipv4::Protocol::l2tp) :
            return header::ipv4::Protocol::l2tp;
        case ToValue(header::ipv4::Protocol::ddx) :
            return header::ipv4::Protocol::ddx;
        case ToValue(header::ipv4::Protocol::iatp) :
            return header::ipv4::Protocol::iatp;
        case ToValue(header::ipv4::Protocol::stp) :
            return header::ipv4::Protocol::stp;
        case ToValue(header::ipv4::Protocol::srp) :
            return header::ipv4::Protocol::srp;
        case ToValue(header::ipv4::Protocol::uti) :
            return header::ipv4::Protocol::uti;
        case ToValue(header::ipv4::Protocol::smp) :
            return header::ipv4::Protocol::smp;
        case ToValue(header::ipv4::Protocol::sm) :
            return header::ipv4::Protocol::sm;
        case ToValue(header::ipv4::Protocol::ptp) :
            return header::ipv4::Protocol::ptp;
        case ToValue(header::ipv4::Protocol::isis_over_ipv4) :
            return header::ipv4::Protocol::isis_over_ipv4;
        case ToValue(header::ipv4::Protocol::fire) :
            return header::ipv4::Protocol::fire;
        case ToValue(header::ipv4::Protocol::crtp) :
            return header::ipv4::Protocol::crtp;
        case ToValue(header::ipv4::Protocol::crudp) :
            return header::ipv4::Protocol::crudp;
        case ToValue(header::ipv4::Protocol::sscopmce) :
            return header::ipv4::Protocol::sscopmce;
        case ToValue(header::ipv4::Protocol::ipcl) :
            return header::ipv4::Protocol::ipcl;
        case ToValue(header::ipv4::Protocol::sps) :
            return header::ipv4::Protocol::sps;
        case ToValue(header::ipv4::Protocol::pipe) :
            return header::ipv4::Protocol::pipe;
        case ToValue(header::ipv4::Protocol::sctp) :
            return header::ipv4::Protocol::sctp;
        case ToValue(header::ipv4::Protocol::fc) :
            return header::ipv4::Protocol::fc;
        case ToValue(header::ipv4::Protocol::rsvp_e2e_ignore) :
            return header::ipv4::Protocol::rsvp_e2e_ignore;
        case ToValue(header::ipv4::Protocol::mobility_header) :
            return header::ipv4::Protocol::mobility_header;
        case ToValue(header::ipv4::Protocol::udplite) :
            return header::ipv4::Protocol::udplite;
        case ToValue(header::ipv4::Protocol::mpls_in_ip) :
            return header::ipv4::Protocol::mpls_in_ip;
        case ToValue(header::ipv4::Protocol::manet) :
            return header::ipv4::Protocol::manet;
        case ToValue(header::ipv4::Protocol::hip) :
            return header::ipv4::Protocol::hip;
        case ToValue(header::ipv4::Protocol::shim6) :
            return header::ipv4::Protocol::shim6;
        case ToValue(header::ipv4::Protocol::wesp) :
            return header::ipv4::Protocol::wesp;
        case ToValue(header::ipv4::Protocol::rohc) :
            return header::ipv4::Protocol::rohc;
        case ToValue(header::ipv4::Protocol::unassigned_143) :
            return header::ipv4::Protocol::unassigned_143;
        case ToValue(header::ipv4::Protocol::unassigned_144) :
            return header::ipv4::Protocol::unassigned_144;
        case ToValue(header::ipv4::Protocol::unassigned_145) :
            return header::ipv4::Protocol::unassigned_145;
        case ToValue(header::ipv4::Protocol::unassigned_146) :
            return header::ipv4::Protocol::unassigned_146;
        case ToValue(header::ipv4::Protocol::unassigned_147) :
            return header::ipv4::Protocol::unassigned_147;
        case ToValue(header::ipv4::Protocol::unassigned_148) :
            return header::ipv4::Protocol::unassigned_148;
        case ToValue(header::ipv4::Protocol::unassigned_149) :
            return header::ipv4::Protocol::unassigned_149;
        case ToValue(header::ipv4::Protocol::unassigned_150) :
            return header::ipv4::Protocol::unassigned_150;
        case ToValue(header::ipv4::Protocol::unassigned_151) :
            return header::ipv4::Protocol::unassigned_151;
        case ToValue(header::ipv4::Protocol::unassigned_152) :
            return header::ipv4::Protocol::unassigned_152;
        case ToValue(header::ipv4::Protocol::unassigned_153) :
            return header::ipv4::Protocol::unassigned_153;
        case ToValue(header::ipv4::Protocol::unassigned_154) :
            return header::ipv4::Protocol::unassigned_154;
        case ToValue(header::ipv4::Protocol::unassigned_155) :
            return header::ipv4::Protocol::unassigned_155;
        case ToValue(header::ipv4::Protocol::unassigned_156) :
            return header::ipv4::Protocol::unassigned_156;
        case ToValue(header::ipv4::Protocol::unassigned_157) :
            return header::ipv4::Protocol::unassigned_157;
        case ToValue(header::ipv4::Protocol::unassigned_158) :
            return header::ipv4::Protocol::unassigned_158;
        case ToValue(header::ipv4::Protocol::unassigned_159) :
            return header::ipv4::Protocol::unassigned_159;
        case ToValue(header::ipv4::Protocol::unassigned_160) :
            return header::ipv4::Protocol::unassigned_160;
        case ToValue(header::ipv4::Protocol::unassigned_161) :
            return header::ipv4::Protocol::unassigned_161;
        case ToValue(header::ipv4::Protocol::unassigned_162) :
            return header::ipv4::Protocol::unassigned_162;
        case ToValue(header::ipv4::Protocol::unassigned_163) :
            return header::ipv4::Protocol::unassigned_163;
        case ToValue(header::ipv4::Protocol::unassigned_164) :
            return header::ipv4::Protocol::unassigned_164;
        case ToValue(header::ipv4::Protocol::unassigned_165) :
            return header::ipv4::Protocol::unassigned_165;
        case ToValue(header::ipv4::Protocol::unassigned_166) :
            return header::ipv4::Protocol::unassigned_166;
        case ToValue(header::ipv4::Protocol::unassigned_167) :
            return header::ipv4::Protocol::unassigned_167;
        case ToValue(header::ipv4::Protocol::unassigned_168) :
            return header::ipv4::Protocol::unassigned_168;
        case ToValue(header::ipv4::Protocol::unassigned_169) :
            return header::ipv4::Protocol::unassigned_169;
        case ToValue(header::ipv4::Protocol::unassigned_170) :
            return header::ipv4::Protocol::unassigned_170;
        case ToValue(header::ipv4::Protocol::unassigned_171) :
            return header::ipv4::Protocol::unassigned_171;
        case ToValue(header::ipv4::Protocol::unassigned_172) :
            return header::ipv4::Protocol::unassigned_172;
        case ToValue(header::ipv4::Protocol::unassigned_173) :
            return header::ipv4::Protocol::unassigned_173;
        case ToValue(header::ipv4::Protocol::unassigned_174) :
            return header::ipv4::Protocol::unassigned_174;
        case ToValue(header::ipv4::Protocol::unassigned_175) :
            return header::ipv4::Protocol::unassigned_175;
        case ToValue(header::ipv4::Protocol::unassigned_176) :
            return header::ipv4::Protocol::unassigned_176;
        case ToValue(header::ipv4::Protocol::unassigned_177) :
            return header::ipv4::Protocol::unassigned_177;
        case ToValue(header::ipv4::Protocol::unassigned_178) :
            return header::ipv4::Protocol::unassigned_178;
        case ToValue(header::ipv4::Protocol::unassigned_179) :
            return header::ipv4::Protocol::unassigned_179;
        case ToValue(header::ipv4::Protocol::unassigned_180) :
            return header::ipv4::Protocol::unassigned_180;
        case ToValue(header::ipv4::Protocol::unassigned_181) :
            return header::ipv4::Protocol::unassigned_181;
        case ToValue(header::ipv4::Protocol::unassigned_182) :
            return header::ipv4::Protocol::unassigned_182;
        case ToValue(header::ipv4::Protocol::unassigned_183) :
            return header::ipv4::Protocol::unassigned_183;
        case ToValue(header::ipv4::Protocol::unassigned_184) :
            return header::ipv4::Protocol::unassigned_184;
        case ToValue(header::ipv4::Protocol::unassigned_185) :
            return header::ipv4::Protocol::unassigned_185;
        case ToValue(header::ipv4::Protocol::unassigned_186) :
            return header::ipv4::Protocol::unassigned_186;
        case ToValue(header::ipv4::Protocol::unassigned_187) :
            return header::ipv4::Protocol::unassigned_187;
        case ToValue(header::ipv4::Protocol::unassigned_188) :
            return header::ipv4::Protocol::unassigned_188;
        case ToValue(header::ipv4::Protocol::unassigned_189) :
            return header::ipv4::Protocol::unassigned_189;
        case ToValue(header::ipv4::Protocol::unassigned_190) :
            return header::ipv4::Protocol::unassigned_190;
        case ToValue(header::ipv4::Protocol::unassigned_191) :
            return header::ipv4::Protocol::unassigned_191;
        case ToValue(header::ipv4::Protocol::unassigned_192) :
            return header::ipv4::Protocol::unassigned_192;
        case ToValue(header::ipv4::Protocol::unassigned_193) :
            return header::ipv4::Protocol::unassigned_193;
        case ToValue(header::ipv4::Protocol::unassigned_194) :
            return header::ipv4::Protocol::unassigned_194;
        case ToValue(header::ipv4::Protocol::unassigned_195) :
            return header::ipv4::Protocol::unassigned_195;
        case ToValue(header::ipv4::Protocol::unassigned_196) :
            return header::ipv4::Protocol::unassigned_196;
        case ToValue(header::ipv4::Protocol::unassigned_197) :
            return header::ipv4::Protocol::unassigned_197;
        case ToValue(header::ipv4::Protocol::unassigned_198) :
            return header::ipv4::Protocol::unassigned_198;
        case ToValue(header::ipv4::Protocol::unassigned_199) :
            return header::ipv4::Protocol::unassigned_199;
        case ToValue(header::ipv4::Protocol::unassigned_200) :
            return header::ipv4::Protocol::unassigned_200;
        case ToValue(header::ipv4::Protocol::unassigned_201) :
            return header::ipv4::Protocol::unassigned_201;
        case ToValue(header::ipv4::Protocol::unassigned_202) :
            return header::ipv4::Protocol::unassigned_202;
        case ToValue(header::ipv4::Protocol::unassigned_203) :
            return header::ipv4::Protocol::unassigned_203;
        case ToValue(header::ipv4::Protocol::unassigned_204) :
            return header::ipv4::Protocol::unassigned_204;
        case ToValue(header::ipv4::Protocol::unassigned_205) :
            return header::ipv4::Protocol::unassigned_205;
        case ToValue(header::ipv4::Protocol::unassigned_206) :
            return header::ipv4::Protocol::unassigned_206;
        case ToValue(header::ipv4::Protocol::unassigned_207) :
            return header::ipv4::Protocol::unassigned_207;
        case ToValue(header::ipv4::Protocol::unassigned_208) :
            return header::ipv4::Protocol::unassigned_208;
        case ToValue(header::ipv4::Protocol::unassigned_209) :
            return header::ipv4::Protocol::unassigned_209;
        case ToValue(header::ipv4::Protocol::unassigned_210) :
            return header::ipv4::Protocol::unassigned_210;
        case ToValue(header::ipv4::Protocol::unassigned_211) :
            return header::ipv4::Protocol::unassigned_211;
        case ToValue(header::ipv4::Protocol::unassigned_212) :
            return header::ipv4::Protocol::unassigned_212;
        case ToValue(header::ipv4::Protocol::unassigned_213) :
            return header::ipv4::Protocol::unassigned_213;
        case ToValue(header::ipv4::Protocol::unassigned_214) :
            return header::ipv4::Protocol::unassigned_214;
        case ToValue(header::ipv4::Protocol::unassigned_215) :
            return header::ipv4::Protocol::unassigned_215;
        case ToValue(header::ipv4::Protocol::unassigned_216) :
            return header::ipv4::Protocol::unassigned_216;
        case ToValue(header::ipv4::Protocol::unassigned_217) :
            return header::ipv4::Protocol::unassigned_217;
        case ToValue(header::ipv4::Protocol::unassigned_218) :
            return header::ipv4::Protocol::unassigned_218;
        case ToValue(header::ipv4::Protocol::unassigned_219) :
            return header::ipv4::Protocol::unassigned_219;
        case ToValue(header::ipv4::Protocol::unassigned_220) :
            return header::ipv4::Protocol::unassigned_220;
        case ToValue(header::ipv4::Protocol::unassigned_221) :
            return header::ipv4::Protocol::unassigned_221;
        case ToValue(header::ipv4::Protocol::unassigned_222) :
            return header::ipv4::Protocol::unassigned_222;
        case ToValue(header::ipv4::Protocol::unassigned_223) :
            return header::ipv4::Protocol::unassigned_223;
        case ToValue(header::ipv4::Protocol::unassigned_224) :
            return header::ipv4::Protocol::unassigned_224;
        case ToValue(header::ipv4::Protocol::unassigned_225) :
            return header::ipv4::Protocol::unassigned_225;
        case ToValue(header::ipv4::Protocol::unassigned_226) :
            return header::ipv4::Protocol::unassigned_226;
        case ToValue(header::ipv4::Protocol::unassigned_227) :
            return header::ipv4::Protocol::unassigned_227;
        case ToValue(header::ipv4::Protocol::unassigned_228) :
            return header::ipv4::Protocol::unassigned_228;
        case ToValue(header::ipv4::Protocol::unassigned_229) :
            return header::ipv4::Protocol::unassigned_229;
        case ToValue(header::ipv4::Protocol::unassigned_230) :
            return header::ipv4::Protocol::unassigned_230;
        case ToValue(header::ipv4::Protocol::unassigned_231) :
            return header::ipv4::Protocol::unassigned_231;
        case ToValue(header::ipv4::Protocol::unassigned_232) :
            return header::ipv4::Protocol::unassigned_232;
        case ToValue(header::ipv4::Protocol::unassigned_233) :
            return header::ipv4::Protocol::unassigned_233;
        case ToValue(header::ipv4::Protocol::unassigned_234) :
            return header::ipv4::Protocol::unassigned_234;
        case ToValue(header::ipv4::Protocol::unassigned_235) :
            return header::ipv4::Protocol::unassigned_235;
        case ToValue(header::ipv4::Protocol::unassigned_236) :
            return header::ipv4::Protocol::unassigned_236;
        case ToValue(header::ipv4::Protocol::unassigned_237) :
            return header::ipv4::Protocol::unassigned_237;
        case ToValue(header::ipv4::Protocol::unassigned_238) :
            return header::ipv4::Protocol::unassigned_238;
        case ToValue(header::ipv4::Protocol::unassigned_239) :
            return header::ipv4::Protocol::unassigned_239;
        case ToValue(header::ipv4::Protocol::unassigned_240) :
            return header::ipv4::Protocol::unassigned_240;
        case ToValue(header::ipv4::Protocol::unassigned_241) :
            return header::ipv4::Protocol::unassigned_241;
        case ToValue(header::ipv4::Protocol::unassigned_242) :
            return header::ipv4::Protocol::unassigned_242;
        case ToValue(header::ipv4::Protocol::unassigned_243) :
            return header::ipv4::Protocol::unassigned_243;
        case ToValue(header::ipv4::Protocol::unassigned_244) :
            return header::ipv4::Protocol::unassigned_244;
        case ToValue(header::ipv4::Protocol::unassigned_245) :
            return header::ipv4::Protocol::unassigned_245;
        case ToValue(header::ipv4::Protocol::unassigned_246) :
            return header::ipv4::Protocol::unassigned_246;
        case ToValue(header::ipv4::Protocol::unassigned_247) :
            return header::ipv4::Protocol::unassigned_247;
        case ToValue(header::ipv4::Protocol::unassigned_248) :
            return header::ipv4::Protocol::unassigned_248;
        case ToValue(header::ipv4::Protocol::unassigned_249) :
            return header::ipv4::Protocol::unassigned_249;
        case ToValue(header::ipv4::Protocol::unassigned_250) :
            return header::ipv4::Protocol::unassigned_250;
        case ToValue(header::ipv4::Protocol::unassigned_251) :
            return header::ipv4::Protocol::unassigned_251;
        case ToValue(header::ipv4::Protocol::unassigned_252) :
            return header::ipv4::Protocol::unassigned_252;
        case ToValue(header::ipv4::Protocol::
            use_for_experimentation_and_testing_1) : 
                return header::ipv4::Protocol::
                    use_for_experimentation_and_testing_1;
        case ToValue(header::ipv4::Protocol::
            use_for_experimentation_and_testing_2) :
                return header::ipv4::Protocol::
                    use_for_experimentation_and_testing_2;
        case ToValue(header::ipv4::Protocol::reserved) :
            return header::ipv4::Protocol::reserved;
    }
    return header::ipv4::Protocol::reserved; 
}

} //!protocol

} //!ipv4

} //!header

#endif //!HEADER_IPV4_PROTOCOL_H_
