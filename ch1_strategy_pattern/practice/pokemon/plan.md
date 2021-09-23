# pokemon

## 神奇寶貝
- 屬性 (max_hp, cur_hp, str, def)
- 招式 (Skill)
    - 招式名稱
    - 招式傷害
    - pp值

```Java
//Design

class Pokemon {
    max_hp, cur_hp, str, def;
    Skill skills[]; // Pokemon has a Skill
    set_skill() {...};
}
// monsters is a Pokemon

interface Skill {
    pp, injury;
    attack(Pokemon attack_pkm, Pokemon attacked_pkm);
}
// skills implement Skill
```


## 參考資料
- C++類別互相引用: https://software.intel.com/content/www/cn/zh/develop/blogs/cc-class-include-each-other.html
- 

