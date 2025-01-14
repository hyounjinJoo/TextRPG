#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "../Item/Item.h"

class Item;

class Character
{
public:
    ~Character();

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
    void GetExperience(int AddExperience);
    void UseItem(int Index);

    std::string GetName() 
    {
        return Instance->Name;
    }
    void SetName(std::string InputName) 
    {
        Instance->Name = InputName;
    }

    const int GetLevel() 
    {
        return Instance->Level;
    }
    void SetLevel(int InputLevel) 
    {
        Instance->Level = InputLevel;
    }

    int GetHealth() 
    {
        return Instance->Health;
    }
    void SetHealth(int InputHealth) 
    {
        Instance->Health = InputHealth;
    }

    const int GetMaxHealth() 
    {
        return Instance->MaxHealth;
    }
    void SetMaxHealth(int InputMaxHealth) {
        Instance->MaxHealth = InputMaxHealth;
    }

    int GetAttack() 
    {
        return Instance->Attack;
    }
    void SetAttack(int InputAttack)
    {
        Instance->Attack = InputAttack;
    }

    int GetExperience() 
    {
        return Instance->Experience;
    }
    void SetExperience(int InputExperience) 
    {
        Instance->Experience = InputExperience;
    }

    int GetGold() 
    {
        return Instance->Gold;
    }
    void SetGold(int InputGold) 
    {
        Instance->Gold = InputGold;
    }

    std::vector<Item*>& GetInventory() 
    {
        return Instance->Inventory;
    }

    // 250113 주현진 추가. GameManager에서 편하게 해당 아이템의 여부를 확인할 수 있도록 추가했음.
    bool IsExistInInventory(int Index)
    {
        return Instance->Inventory[Index] ? true : false;
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
