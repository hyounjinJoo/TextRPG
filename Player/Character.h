#pragma once
#include <string>
#include <vector>

class Item;

class Character
{
private:
    Character(std::string Name);
    ~Character();

    Character(const Character&) = delete;
    Character& operator=(const Character&) = delete;

#pragma region Declare Singletone
public:
    static Character* GetInstance(std::string Name = "")
    {
        if(!Instance)
        {
            Instance = new Character(Name);
        }

        return Instance;
    }
    
private:
    static Character* Instance;    
#pragma endregion
    
public:
    void DisplayStatus();
    void LevelUp();
    void UseItem(int Index);
    void VisitShop();
    int GetGold() 
    {
        return Instance->Gold;
    }
    void SetGold(int InputGold) 
    {
        Instance->Gold = InputGold;
    }

private:
    std::string Name;
    int Level;
    int Health;
    int MaxHealth;
    int Attack;
    int Experience;
    int Gold;
    std::vector<Item*> Inventory; 
};
