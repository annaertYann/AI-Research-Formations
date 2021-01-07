#pragma once
#define SAFE_DELETE(p) if (p) { delete (p); (p) = nullptr; }
#define PLAYERTAG 0
#define CompanionTAG -1