#ifndef CONSTANTS_HPP_
#define CONSTANTS_HPP_

#include <string>
#include "abcg.hpp"
#include <imgui.h>
#include <vector>

class Constants {
 public:
    // Shaders
    std::vector<const char*> m_shaderNames {
        "normalmapping", "texture"
    };

    const char* lbMarkLight = "Ajuda (?)";
    const char* descMarkLight = "Mova os sliders entre os valores -1 e 1 para alterar a direção da Luz incidente no Planeta nos eixos XYZ.";

    const char* lbMarkInfo = "Mais Informações (?)";

    ImVec4 yellow{1, 1, 0, 1};
    glm::vec4 sunLightDir{0.0f, 0.0f, -1.0f, 1.0f};

    // Earth Variants
    std::vector<const char*> m_earthTextures {
        "Default", "Politico", "Noturno", "NoWater"};

    // Planets
    std::vector<const char*> m_planetNames {
        "Sol", "Mercurio", "Venus", "Terra", "Lua", "Marte", "Jupiter",
        "Saturno", "Urano", "Netuno", "Ceres", "Haumea", "Makemake", "Eris"};

    std::vector<const char*> descMarkPlanets {
        "O Sol é a estrela central do Sistema Solar.\nTemperatura na superfície: 5.778 K.\nDistância da Terra: 149.600.000 km.\nIdade: 4,603 × 10^9 anos.\nMassa: 1,989 × 10^30 kg.\nRaio: 696.340 km.\nGravidade: 274 m/s².",

        "Mercúrio é o menor e mais interno planeta do Sistema Solar.\nDistância do Sol: 57.910.000 km.\nDuração do dia: 58d 15h 30m.\nÁrea da superfície: 74.800.000 km².\nPeríodo orbital: 88 dias.\nGravidade: 3,7 m/s².\nMassa: 3,285 × 10^23 kg.\nRaio: 2.439,7 km.",

        "Vênus é o segundo planeta do Sistema Solar em ordem de distância a partir do Sol, orbitando-o a cada 224,7 dias.\nDistância do Sol: 108.200.000 km.\nÁrea da superfície: 460.200.000 km².\nDuração do dia: 116d 18h 0m.\nRaio: 6.051,8 km.\nGravidade: 8,87 m/s².\nMassa: 4,867 × 10^24 kg.",

        "A Terra é o terceiro planeta mais próximo do Sol, o mais denso e o quinto maior dos oito planetas do Sistema Solar.\nLuas: Lua.\nIdade: 4,543 × 10^9 anos.\nPeríodo orbital: 365 dias.\nDistância do Sol: 149.600.000 km.\nÁrea da superfície: 510.100.000 km².\nÁrea: 148.900.000 km².\nPopulação: 7,753 bilhões (2020).",

        "A Lua é o único satélite natural da Terra e o quinto maior do Sistema Solar.\nDistância da Terra: 384.400 km.\nDiâmetro equatorial: 3474,8 km.\nÁrea da superfície: 3,793 x 107 km².\nPeríodo orbital: 27,321582 d.",

        "Marte é o quarto planeta a partir do Sol, o segundo menor do Sistema Solar.\nLuas: Fobos, Deimos.\nGravidade: 3,721 m/s².\nRaio: 3.389,5 km.\nDuração do dia: 1d 0h 37m.\nÁrea da superfície: 144.800.000 km².\nPeríodo orbital: 687 dias.\nMassa: 6,39 × 10^23 kg.",

        "Júpiter é o maior planeta do Sistema Solar, tanto em diâmetro quanto em massa e é o quinto mais próximo do Sol.\nLuas: Europa, Ganímedes, Io, Calisto, Amalteia, Himalia, Carme,.\nÁrea da superfície: 6,142 × 10^10 km².\nMassa: 1,898 × 10^27 kg.\nGravidade: 24,79 m/s².\nRaio: 69.911 km.\nDuração do dia: 0d 9h 56m.\nPeríodo orbital: 12 anos.",

        "Saturno é o sexto planeta a partir do Sol e o segundo maior do Sistema Solar.\nLuas: Titã, Encélado, Mimas, Jápeto, Dione, Tétis, Pã, Reia.\nDistância do Sol: 1,434 × 10^9 km.\nÁrea da superfície: 4,27 × 10^10 km².\nDuração do dia: 0d 10h 42m.\nRaio: 58.232 km.\nMassa: 5,683 × 10^26 kg (95,16 M⊕).\nGravidade: 10,44 m/s².",

        "Urano é o sétimo planeta a partir do Sol, o terceiro maior e o quarto mais massivo dos oito planetas do Sistema Solar.\nLuas: Umbriel, Titânia, Oberon, Miranda, Ariel, Puck, Créssida.\nDistância do Sol: 2,871 × 10^9 km.\nÁrea da superfície: 8,083 × 10^9 km².\nDescobrimento: 13 de março de 1781.\nDuração do dia: 0d 17h 14m.\nGravidade: 8,87 m/s².\nMassa: 8,681 × 10^25 kg.",

        "Netuno ou Neptuno é o oitavo planeta do Sistema Solar, o último a partir do Sol desde a reclassificação de Plutão para a categoria de planeta anão.\nLuas: Tritão, Hipocampo, Proteu, Nereida, Talassa, Despina.\nDistância do Sol: 4,495 × 10^9 km.\nÁrea da superfície: 7,618 × 10^9 km².\nDuração do dia: 0d 16h 6m.\nDescobrimento: 23 de setembro de 1846.\nPeríodo orbital: 165 anos.\nRaio: 24.622 km.",

        "Ceres é um planeta anão localizado no cinturão de asteroides entre Marte e Júpiter.\nGravidade: 0,27 m/s².\nOrbita: Sol.\nMassa: 9,5×1020 kg.\nSemieixo maior: 2,7663 UATemperatura: média: -106 ºC; mínima: S.D. ºC; máxima: -34 ºC.\nPeríodo de rotação: 0,3781 d.\nVelocidade orbital média: 17,882 km/s.",

        "Haumea, com a designação de planeta anão 136108 Haumea.\nGravidade: 0,401 m/s².\nRaio: 816 km.\nDensidade: 2,6 g/cm³.\nTemperatura: média: -223,2 ºC.\nLuas: Hi'iaka, Namaka.",

        "Makemake é o terceiro maior planeta anão do Sistema Solar.\nDistância da Terra: 5,61 × 10^9 km.\nVolume: ~ 1,7×109 km³.\nTemperatura: média: −243 ºC.\nPeríodo de rotação: 7,771 ± 0,003 horas.\nDensidade média: 1,4-3,2 g/cm³.",

        "Éris ou informalmente conhecido Décimo Planeta, é um planeta anão plutoide situado nos confins do sistema solar.\nPeríodo orbital: 558 anos.\nDescobrimento: 5 de janeiro de 2005.\nGravidade: 0,82 m/s².\nRaio: 1.163 km.\nDensidade: 2,52 g/cm³.\nLua: Disnomia."
    };
};

#endif