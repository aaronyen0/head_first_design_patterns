class Pokemon {
public:
    int str;
    int def;
    int max_hp;
    int cur_hp;
    Skill skills[4] = {0};
    void set_skill(Skill skill, int skill_id) {
        if (skill_id < 4) {
            skills[skill_id] = skill;
        }
    }
}

class Monster1 : public Pokemon {
    Monster1() {
        str = 10;
        def = 20;
        max_hp = 99;
        cur_hp = 99;
        skills[0] = new SkillA();
    }
};

class Monster2 : public Pokemon {
    Monster1() {
        str = 20;
        def = 10;
        max_hp = 80;
        cur_hp = 80;
        skills[0] = new SkillB();
    }
};


// interface
class Skill {
    string name;
    int injury;
    int pp;
    virtual int attack(Pokemon& attack_pkm, Pokemon& attacked_pkm) = 0;
};

class SkillA : public Skill {
public:
    SkillA() {
        name = "skill_A";
        injury = 5;
        pp = 40;
    }

    int attack(Pokemon& attack_pkm, Pokemon& attacked_pkm) {
        int hurt = max(1, injury * attack_pkm.str - attacked_pkm.def);
        hurt = min(attacked_pkm.hp, hurt);
        attacked_pkm.hp -= hurt;
        return hurt
    }
};

class SkillB : public Skill {
public:
    SkillB() {
        name = "skill_B";
        injury = 3;
        pp = 10;
    }

    int attack(Pokemon& attack_pkm, Pokemon& attacked_pkm) {
        int hurt = min(attacked_pkm.hp, injury);
        attacked_pkm.hp -= hurt;
        return hurt
    }
};