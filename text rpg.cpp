#include <iostream>
#include <map>
#include <string>
#include <vector>

// Equipment slots
// =========================
enum class EquipSlots
{
    WEAPON,
    HEADGEAR,
    CHESTBODY,
    FOOTWEAR,
    ACCESSORY
};

struct Weapon
{
    std::wstring name;
    int power;
};

class Enemy
{
private:
    std::wstring m_Name;
    int m_Health;
    int m_Defence;
    int m_AttackPower;

public:
    Enemy(const std::wstring& name, int health, int defence, int attackPower)
        : m_Name(name), m_Health(health), m_Defence(defence), m_AttackPower(attackPower) {}

    int TakeDamage(int attackPower)
    {
        int damage = attackPower - m_Defence;
        if (damage < 0)
        {
            damage = 0;
        }
        if (damage > m_Health)
        {
            damage = m_Health;
        }
        m_Health -= damage;
        return damage;
    }

    const std::wstring& GetName() const { return m_Name; }
    int GetHealth() const { return m_Health; }
    int GetAttackPower() const { return m_AttackPower; }
};

class Stats
{
private:
    std::map<std::wstring, int> m_StatList;
    std::map<std::wstring, int> m_StatModifierList;
    std::map<EquipSlots, int> m_EquipSlotList;

public:
    Stats(int strength, int intelligence, int speed, int dexterity, int stamina)
        : m_StatList{
              {L"Attack", 0},
              {L"Defence", 0},
              {L"Magic", 0},
              {L"Strength", strength},
              {L"Intelligence", intelligence},
              {L"Speed", speed},
              {L"Dexterity", dexterity},
              {L"Stamina", stamina}},
          m_StatModifierList{
              {L"Strength", 0},
              {L"Intelligence", 0},
              {L"Speed", 0},
              {L"Dexterity", 0},
              {L"Stamina", 0}},
          m_EquipSlotList{
              {EquipSlots::WEAPON, 0},
              {EquipSlots::HEADGEAR, 0},
              {EquipSlots::CHESTBODY, 0},
              {EquipSlots::FOOTWEAR, 0},
              {EquipSlots::ACCESSORY, 0}}
    {
        UpdateStats();
    }

    int GetStat(const std::wstring& key) const
    {
        const auto it = m_StatList.find(key);
        if (it == m_StatList.end())
        {
            std::wcerr << L"[" << key << L"] is not a valid stat\n";
            return 0;
        }
        return it->second;
    }

    int GetStatModifier(const std::wstring& key) const
    {
        const auto it = m_StatModifierList.find(key);
        if (it == m_StatModifierList.end())
        {
            std::wcerr << L"[" << key << L"] is not a valid stat modifier\n";
            return 0;
        }
        return it->second;
    }

    int GetEquipmentValue(EquipSlots slot) const
    {
        const auto it = m_EquipSlotList.find(slot);
        if (it == m_EquipSlotList.end())
        {
            std::wcerr << L"Invalid equipment slot\n";
            return 0;
        }
        return it->second;
    }

    void SetStat(const std::wstring& key, int value)
    {
        const auto it = m_StatList.find(key);
        if (it == m_StatList.end())
        {
            std::wcerr << L"[" << key << L"] is not a valid stat\n";
            return;
        }
        it->second = value;
    }

    void SetModifier(const std::wstring& key, int value)
    {
        const auto it = m_StatModifierList.find(key);
        if (it == m_StatModifierList.end())
        {
            std::wcerr << L"[" << key << L"] is not a valid stat modifier\n";
            return;
        }
        it->second = value;
    }

    void SetEquipmentValue(EquipSlots slot, int value)
    {
        const auto it = m_EquipSlotList.find(slot);
        if (it == m_EquipSlotList.end())
        {
            std::wcerr << L"Invalid equipment slot\n";
            return;
        }
        it->second = value;
    }

    void UpdateStats()
    {
        m_StatList[L"Attack"] =
            m_EquipSlotList[EquipSlots::WEAPON] +
            m_StatList[L"Strength"] + m_StatModifierList[L"Strength"] +
            (m_StatList[L"Intelligence"] + m_StatModifierList[L"Intelligence"]) / 5 +
            (m_StatList[L"Speed"] + m_StatModifierList[L"Speed"]) / 5 +
            (m_StatList[L"Dexterity"] + m_StatModifierList[L"Dexterity"]) / 5;
    }
};

int main()
{
    Stats playerStats(10, 12, 12, 20, 0);

    const std::vector<Weapon> weapons{
        {L"Wooden Club", 10},
        {L"Iron Sword", 25},
        {L"Battle Axe", 35},
        {L"Gun", 50}};

    // Choose a weapon by index: 0 = club, 1 = sword, 2 = axe, 3 = gun.
    const std::size_t selectedWeaponIndex = 3;
    const Weapon& selectedWeapon = weapons[selectedWeaponIndex];
    playerStats.SetEquipmentValue(EquipSlots::WEAPON, selectedWeapon.power);

    playerStats.SetModifier(L"Strength", 5);
    playerStats.SetModifier(L"Speed", 3);
    playerStats.SetStat(L"Defence", 8);
    playerStats.UpdateStats();

    std::wcout << L"=====================================\n";
    std::wcout << L"PLAYER STATS\n";
    std::wcout << L"=====================================\n";
    std::wcout << L"Attack: " << playerStats.GetStat(L"Attack") << L"\n";
    std::wcout << L"Defence: " << playerStats.GetStat(L"Defence") << L"\n";
    std::wcout << L"Magic: " << playerStats.GetStat(L"Magic") << L"\n";
    std::wcout << L"Strength: " << playerStats.GetStat(L"Strength") << L"\n";
    std::wcout << L"Speed: " << playerStats.GetStat(L"Speed") << L"\n";
    std::wcout << L"Intelligence: " << playerStats.GetStat(L"Intelligence") << L"\n";
    std::wcout << L"Dexterity: " << playerStats.GetStat(L"Dexterity") << L"\n";
    std::wcout << L"Stamina: " << playerStats.GetStat(L"Stamina") << L"\n\n";

    std::wcout << L"Strength Modifier: " << playerStats.GetStatModifier(L"Strength") << L"\n";
    std::wcout << L"Speed Modifier: " << playerStats.GetStatModifier(L"Speed") << L"\n";
    std::wcout << L"Intelligence Modifier: " << playerStats.GetStatModifier(L"Intelligence") << L"\n";
    std::wcout << L"Dexterity Modifier: " << playerStats.GetStatModifier(L"Dexterity") << L"\n";
    std::wcout << L"Stamina Modifier: " << playerStats.GetStatModifier(L"Stamina") << L"\n\n";

    std::wcout << L"Weapon: " << selectedWeapon.name << L" (power "
               << playerStats.GetEquipmentValue(EquipSlots::WEAPON) << L")\n";
    std::wcout << L"Headgear: " << playerStats.GetEquipmentValue(EquipSlots::HEADGEAR) << L"\n";
    std::wcout << L"Chestwear: " << playerStats.GetEquipmentValue(EquipSlots::CHESTBODY) << L"\n";
    std::wcout << L"Footwear: " << playerStats.GetEquipmentValue(EquipSlots::FOOTWEAR) << L"\n";
    std::wcout << L"Accessory: " << playerStats.GetEquipmentValue(EquipSlots::ACCESSORY) << L"\n\n";

    Enemy enemy(L"Goblin", 100, 8, 20);
    int playerHealth = 100;
    int hitNumber = 0;

    std::wcout << L"\nFIGHT! Player health: " << playerHealth << L"\n";
    while (enemy.GetHealth() > 0 && playerHealth > 0)
    {
        // Each consecutive hit adds 5 attack power.
        const int attackPower = playerStats.GetStat(L"Attack") + hitNumber * 5;
        const int damageDealt = enemy.TakeDamage(attackPower);
        ++hitNumber;

        std::wcout << L"You hit the " << enemy.GetName() << L" with the "
                   << selectedWeapon.name << L" for " << damageDealt << L" damage.\n";
        std::wcout << enemy.GetName() << L" has " << enemy.GetHealth()
                   << L" health remaining.\n";

        if (enemy.GetHealth() > 0)
        {
            int damageTaken = enemy.GetAttackPower() - playerStats.GetStat(L"Defence");
            if (damageTaken < 0)
            {
                damageTaken = 0;
            }
            if (damageTaken > playerHealth)
            {
                damageTaken = playerHealth;
            }
            playerHealth -= damageTaken;

            std::wcout << enemy.GetName() << L" counterattacks for "
                       << damageTaken << L" damage. Player health: "
                       << playerHealth << L"\n";
        }
    }

    if (enemy.GetHealth() == 0)
    {
        std::wcout << L"You defeated the " << enemy.GetName() << L"!\n";
    }
    else
    {
        std::wcout << L"You were defeated!\n";
    }

    return 0;
}
