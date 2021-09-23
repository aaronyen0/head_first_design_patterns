# Strategy Pattern
定義了演算法家族，個別封裝起來，讓他們可以自由的替換，此模式讓演算法的變動，不會影響到使演算法的程式
- 設計守則: 找出程式中可能變動的部分，並將她們獨立出來，不要和那些不需要更動的程式碼混在一起
- 設計守則: 寫程式是針對介面而寫，而不是針對實踐方式而寫
- 設計守則: 多用合成，少用繼承
- 設計理念: 讓系統中的某部分改變不會影響其他部分

## keywords
- strategy pattern
- HAS-A
- IS-A
- IMPLEMENT
- superclass
- interface
- composition
- 抽象
- 封裝
- 多形
- 繼承


# 情境: 設計一個鴨子

## 1. 設計一個鴨子超類別，所有鴨子都繼承他
如果都簡單繼承Duck，當鴨子有許多種類的quack時
- 程式碼在多個次類別容易重複
- 執行期的行為不容易改變
- 改變會牽一髮而動全身，造成其他鴨子不想要的改變
- 難以得知所有鴨子的行為 (假設有一百隻)

**當涉及到維護時，以「再利用」為目的使用繼承結果未必完美**
```Java
class Duck{
    display() {}
    swim() {}
    fly() {}
    quack() {}
}

class MallarDuck extends Duck {
    display() {綠頭}
}

class RedheadDuck extends Duck {
    display() {紅頭}
}

class RubberDuck extends Duck {
    display() {橡膠}
    quack() {吱吱叫}
    fly() {不會飛}
}

class DecoyDuck extends Duck {
    display() {誘餌鴨}
    quack() {不會叫}
    fly() {不會飛}
}
```


## 2. 將變動的fly和quack設計成interface
如果將會不會飛以及會不會叫各自獨立成interface，反而讓重複的程式碼更多了
```Java
class Duck{
    display()
    swim()
}

interface Flyable {
    fly()
}

interface Quackable {
    quack()
}

class MallarDuck extends Duck implements Flyable, Quackable {
    display() {綠頭}
    fly() {會飛}
    quack() {呱呱叫}
}

class RedheadDuck extends Duck implements Flyable, Quackable {
    display() {紅頭}
    fly() {會飛}
    quack() {呱呱叫}
}

class RubberDuck extends Duck implements Quackable {
    display() {橡膠}
    quack() {吱吱}
}

class DecoyDuck extends Duck {
    display() {誘餌鴨}
}
```


## 3 將會變動的部分取出並「封裝」起來
- 分開會變動(fly, quack)及不太會變動的部分
- 增加兩個interface
    - FlyBehavior
    - QuackBehavior
- 直接遊行為類別實現行為介面，不再由鴨子類別自己處理
- 這樣的設計能讓飛行和呱呱叫的行為被其他物件再三利用
- 新增一種飛行或是叫聲也不會影響現有的鴨子

```Java
interface FlyBehavior {
    fly()
}

class FlyWithWings implements FlyBehavior {
    fly() {用翅膀飛}
}

class FlyNoWay implements FlyBehavior {
    fly() {不會飛}
}
```

```Java
interface QuackBehavior {
    quack()
}

class Quack implements QuackBehavior {
    quack() {呱呱叫}
}

class Squeak implements FlyBehavior {
    quack() {吱吱叫}
}

class MuteQuack implements FlyBehavior {
    quack() {不會叫}
}
```


## 4. 承3，將行為封裝之後，如何整合在鴨子內
- 在鴨子中宣告「介面型態」，這個型態可以支援所有實作這個介面的物件

```Java
class Duck {
    FlyBehavior flyBehavior;
    QuackBehavior quackBehavior;

    display() {}
    swim() {}

    performFly() {
        flyBehavior.fly(); //將動作委派行為類別處理
    }
    performQuack() {
        quackBehavior.quack();
    }
    setFlyBehavior(FlyBehavior fb) {
        flyBehavior = fb; //可以在執行期間更新鴨子行為
    }
    setQuackBehavior(QuackBehavior qb) {
        quackBehavior = qb;
    }
}

class MallarDuck extends Duck {
    flyBehavior = new FlyWithWings();
    quackBehavior = new Quack();
}

```

# 要點
- 良好的OO設計必須具備三個特性
    - 可再利用
    - 可擴充
    - 可維護
- 模式不是程式碼，而是針對特定問題的解決方案
- 大多數的模式都著眼在軟體改變的議題上
- 大多數的模式都允許系統局部改變，而不影響其他部分
- 我們常把系統中，會變動的部分抽出來封裝
- 模式讓開發者有共同詞彙，提高合作效率