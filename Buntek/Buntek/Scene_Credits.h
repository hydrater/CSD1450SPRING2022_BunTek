#include "System.h"

class Scene_Credits : public Scene
{
public:
    void Start(void) override;
    //void EarlyUpdate(void) override;
    void Update(void) override;
    //void LateUpdate(void) override;
private:
    ~Scene_Credits(void) override;
    GameObject* header = 0, * credits = 0, * bottom = 0;
    //TextRenderer* displayTxt = 0;

};
