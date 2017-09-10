#pragma once

void DB_InitStream();
void DB_InitStreamOut();
void DB_FreeStreamOut();
void DB_WriteDataToStream(char DoWrite_, byte_t* Data_, int Size_, int *pStreamOutPos_);
void DB_ProcessDelayedStream();

