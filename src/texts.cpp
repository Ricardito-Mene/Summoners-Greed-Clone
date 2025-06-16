#include "texts.h"

// Definição das variáveis globais
const char* Strings[(int)STRING_COUNT * (int)LOCALIZATION_COUNT] = { nullptr };
Localization localization = LOCALIZATION_ENG;

void init_strings()
{
  Strings[(int)LOCALIZATION_ENG * STRING_COUNT + (int)STRING_CELESTE_CLONE] = "Celeste Clone";
  Strings[(int)LOCALIZATION_ENG * STRING_COUNT + (int)STRING_MADE_IN_CPP] = "Made in C++";

  Strings[(int)LOCALIZATION_GER * STRING_COUNT + (int)STRING_CELESTE_CLONE] = "Celeste Klon";
  Strings[(int)LOCALIZATION_GER * STRING_COUNT + (int)STRING_MADE_IN_CPP] = "Geschrieben in C++";
}

const char* _(StringID stringID)
{
  return Strings[(int)localization * (int)STRING_COUNT + (int)stringID];
}
