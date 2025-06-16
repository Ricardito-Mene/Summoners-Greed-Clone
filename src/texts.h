#pragma once

enum Localization
{
  LOCALIZATION_ENG,
  LOCALIZATION_GER,

  LOCALIZATION_COUNT
};

enum StringID
{
  STRING_CELESTE_CLONE,
  STRING_MADE_IN_CPP,

  STRING_COUNT
};

// Declara variáveis globais (definidas em texts.cpp)
extern const char* Strings[(int)STRING_COUNT * (int)LOCALIZATION_COUNT];
extern Localization localization;

// Inicializa as strings (chame no início do programa)
void init_strings();

// Função para obter texto da localização atual
extern const char* _(StringID stringID);
