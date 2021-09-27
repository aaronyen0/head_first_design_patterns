# Observer Pattern (publish-subscribe)
定義物件之間一種一對多的依賴關係，當一個物件狀態發生改變時，所有依賴於他的物件都將自動地得到通知且被更新。
觀察者模式即是透過實現「依賴倒置原則(DIP)」與「開閉原則(OCP)」，以防止「相關物件為保持一致性，而產生之緊密耦合」。
- 設計守則: 設計時，盡量讓需要互動的物件之間關係鬆綁

# keywords
- observer pattern
- publish subscribe
- dependants 
- coupling
- subject
- observer
- 開閉原則 (Open-Closed Principle, OCP)
- 依賴倒置原則 (DIP)



# 情境
建立一個氣象觀測物件，該物件追蹤
- 溫度
- 濕度
- 氣壓
並需要建立並隨時更新多個布告板，每個布告板會根據溫度、濕度、氣壓更新
- 目前狀況
- 氣象統計
- 天氣預報
而且這個系統需要可擴充，讓其他開發者可以插入新的布告板


## 1. 設計一個WwatherData包含資料更新及布告更新
此版本的問題
- 針對實踐寫程式，而非針對介面
- 對於每個新的布告板，我們都得更動程式碼
- 無法在執行期動態的增加或是刪除布告板
- 尚未封裝改變的部分

```Java
class WeatherData {
    getTemperature() {...}
    getHumidity() {...}
    getPressure() {...}
    measurementsChanged() {
        // 實作三個看板的更新方法
        float temp = getTemperature();
        float humidity = getHumidity();
        float pressure = getPressure();

        currentConditionsDisplay.update(temp, humidity, pressure);
        statisticsDisplay.update(temp, humidity, pressure);
        forecaseDisplay.update(temp, humidity, pressure);
    }
}
```


## 2. 出版者 + 訂閱者 = 觀察者模式
- 主題物件 (Subject)
    - 管理某些資料
    - 資料改變就會通知觀察者
    - 一旦資料改變，新的資料會以某種形式送到觀察者手上
    - 每個物件都可以有很多觀察者

- 觀察者物件 (Observer)
    - 向主題訂閱(註冊)，以便主題資料更新時，能收到通知

- 

```Java
// 主題物件
interface Subject {
    registerObserver();
    removeObserver();
    notifyObserver();
}

class ConcreteSubject implements Subject {
    registerObserver() {...}
    removeObserver() {...}
    notifyObserver() {...} //此方法負責更新訂閱者

    getState() // 具象的主題還會有一些設定及取得狀態的方法
    setState()
}

```

```Java
// 觀察者物件
interface Observer {
    update();
}

class ConcreteObserver implements Observer {
    // 具象的觀察者必須要實踐這個介面，以便被更新
    update() {...}
}
```


## 3. 鬆綁的威力
當兩個物件被鬆綁，他們依然可以互動，但是不太清楚彼此的細節
觀察者模式中，提供了一個方式讓主題跟觀察者鬆綁
- 從主題的角度，他只知道觀察者有實作特定介面，但他不知道觀察者的細節甚至具體的類別
- 任何時候都可以加入或是移除觀察者
- 有新型態的觀察者出現，主題完全不用改程式碼，新的觀察者只要實踐觀察者介面即可
- 可以在其他地方運用主題及觀察者，並不用將兩者綁在一起
- 片免的改變主題或是觀察者，只要介面仍被遵守，就不會影響對方

**鬆綁設計讓我們建立有彈性的OO系統，能因應變化，因為物件之間的相依度被降到最低**


## 4. 設計布告板
```Java
interface DisplyElement {
    // 實際布告板除了要繼承觀察者介面，同時也應該繼承布告板介面
    // 畢竟未來需要資料的不一定是布告板，也可以是氣象愛好者、分析人員、新聞報導
    display();
}

class CurrentConditionsDisplay implements Observer, DisplayElement {
    update() {...}
    display() {/* display current measurement */}
}

class StatisticsDisplay implements Observer, DisplayElement {
    update() {...}
    display() {/* display the average, min and max measurements */}
}

class ForecastDisplay implements Observer, DisplayElement {
    update() {...}
    display() {/* display the forecast */}
}

class ThirdPartyDisplay implements Observer, DisplayElement {
    update() {...}
    display() {/* display something else based on measurements */}
}

```


## 實踐氣象站
```Java
public interface Subject {
    public void registerObserver(Observer obj);
    public void removeObserver(Observer obj);
    public void notifyObservers();
}

public interface Observer {
    public void update(float temp, float humidity, float pressure);
}

public interface DisplayElement {
    public void display();
}
```










# 參考資料
- 深入淺出設計模式: 觀察者模式
- 觀察者模式: https://notfalse.net/10/observer-pattern#3