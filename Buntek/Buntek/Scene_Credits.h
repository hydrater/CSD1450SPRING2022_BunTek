#include "System.h"

class Scene_Credits : public Scene
{
public:
    void Start(void) override;
    //void EarlyUpdate(void) override;
    void Update(void) override;
    //void LateUpdate(void) override;
    GameObject* GetObjRef(short type);
    const Vector2 backBtnPos = Vector2(-670, 400);
private:
    ~Scene_Credits(void) override;
    GameObject* header = 0, * buntek = 0, *professors = 0, * bottom = 0, *buntekheader = 0, *professorheader = 0, *schoolheader = 0, *school = 0, *presidentheader =0 , *president = 0, *executives = 0, *executivesheader = 0, *softwareHeader = 0, *software = 0, *backBtn = 0;
    //TextRenderer* displayTxt = 0;

};
