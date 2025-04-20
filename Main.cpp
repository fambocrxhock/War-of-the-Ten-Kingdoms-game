#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>
#include <algorithm>

using namespace std;

class Country {
public:
    string name;
    int population;
    int economy;
    int military;
    int technology;
    vector<string> allies;
    vector<string> enemies;

    Country() : name(""), population(0), economy(0), military(0), technology(0) {}

    Country(string n, int pop, int eco, int mil, int tech)
        : name(n), population(pop), economy(eco), military(mil), technology(tech) {}

    void displayStatus() {
        cout << "\n=== " << name << " 當前狀態 ===" << endl;
        cout << "人口: " << population << " 百萬" << endl;
        cout << "經濟: " << economy << "/100" << endl;
        cout << "軍事: " << military << "/100" << endl;
        cout << "科技: " << technology << "/100" << endl;

        if (!allies.empty()) {
            cout << "盟友: ";
            for (const auto& ally : allies) {
                cout << ally << " ";
            }
            cout << endl;
        }

        if (!enemies.empty()) {
            cout << "敵對: ";
            for (const auto& enemy : enemies) {
                cout << enemy << " ";
            }
            cout << endl;
        }
    }
};

class WorldConquestGame {
private:
    map<string, Country> countries;
    string playerCountry;
    int currentYear;
    bool gameOver;

public:
    WorldConquestGame() : currentYear(2023), gameOver(false) {
        initializeCountries();
    }

    void initializeCountries() {
        countries["國家1"] = Country("國家1", 331, 90, 95, 95);
        countries["國家2"] = Country("國家2", 1412, 85, 90, 85);
        countries["國家3"] = Country("國家3", 146, 70, 85, 80);
        countries["國家4"] = Country("國家4", 67, 80, 75, 85);
        countries["國家5"] = Country("國際5", 65, 78, 75, 83);
        countries["國家6"] = Country("國家6", 83, 85, 70, 88);
        countries["國家7"] = Country("國家7", 126, 82, 65, 90);
        countries["國家8"] = Country("國家8", 1408, 75, 80, 70);
        countries["國家9"] = Country("國家9", 213, 72, 60, 65);
        countries["國際10"] = Country("國家10", 26, 79, 65, 82);
    }

    void startGame() {
        cout << "===== 十國爭霸：世界征服遊戲 =====" << endl;
        cout << "請選擇你的國家：" << endl;

        int index = 1;
        for (const auto& pair : countries) {
            cout << index++ << ". " << pair.first << endl;
        }

        int choice;
        cout << "輸入選擇 (1-10): ";
        cin >> choice;

        index = 1;
        for (const auto& pair : countries) {
            if (index++ == choice) {
                playerCountry = pair.first;
                break;
            }
        }

        cout << "\n你選擇了 " << playerCountry << " 作為你的國家！" << endl;
        cout << "目標：在10年內成為世界上最強大的國家！" << endl;

        playGame();
    }

    void playGame() {
        while (!gameOver && currentYear < 2033) {
            cout << "\n======= 年份: " << currentYear << " =======" << endl;
            countries[playerCountry].displayStatus();

            cout << "\n你可以採取的行動：" << endl;
            cout << "1. 發展經濟" << endl;
            cout << "2. 增強軍事" << endl;
            cout << "3. 投資科技" << endl;
            cout << "4. 外交行動" << endl;
            cout << "5. 發動戰爭" << endl;
            cout << "6. 查看其他國家狀態" << endl;
            cout << "7. 結束遊戲" << endl;

            int choice;
            cout << "輸入你的選擇 (1-7): ";
            cin >> choice;

            switch (choice) {
            case 1:
                developEconomy();
                break;
            case 2:
                strengthenMilitary();
                break;
            case 3:
                investTechnology();
                break;
            case 4:
                diplomaticActions();
                break;
            case 5:
                declareWar();
                break;
            case 6:
                viewOtherCountries();
                break;
            case 7:
                gameOver = true;
                break;
            default:
                cout << "無效選擇！" << endl;
            }

            if (!gameOver) {
                simulateWorldEvents();
                checkWinCondition();
                currentYear++;
            }
        }

        endGame();
    }

    void developEconomy() {
        Country& country = countries[playerCountry];
        int improvement = rand() % 10 + 5;
        country.economy = min(100, country.economy + improvement);
        cout << "你成功發展了經濟！經濟增長了 " << improvement << " 點。" << endl;
    }

    void strengthenMilitary() {
        Country& country = countries[playerCountry];
        int improvement = rand() % 8 + 4;
        country.military = min(100, country.military + improvement);
        cout << "你增強了軍事力量！軍事增長了 " << improvement << " 點。" << endl;
    }

    void investTechnology() {
        Country& country = countries[playerCountry];
        int improvement = rand() % 6 + 3;
        country.technology = min(100, country.technology + improvement);
        cout << "你投資了科技研發！科技增長了 " << improvement << " 點。" << endl;
    }

    void diplomaticActions() {
        cout << "\n可進行外交的國家：" << endl;
        vector<string> otherCountries;

        for (const auto& pair : countries) {
            if (pair.first != playerCountry) {
                otherCountries.push_back(pair.first);
            }
        }

        for (int i = 0; i < otherCountries.size(); i++) {
            cout << i + 1 << ". " << otherCountries[i] << endl;
        }

        int choice;
        cout << "選擇國家 (1-9): ";
        cin >> choice;
        string targetCountry = otherCountries[choice - 1];

        cout << "\n外交選項：" << endl;
        cout << "1. 建立同盟" << endl;
        cout << "2. 解除同盟" << endl;
        cout << "3. 貿易協定" << endl;
        cout << "4. 技術交流" << endl;
        cout << "選擇行動 (1-4): ";
        cin >> choice;

        Country& player = countries[playerCountry];
        Country& target = countries[targetCountry];

        switch (choice) {
        case 1: {
            if (find(player.allies.begin(), player.allies.end(), targetCountry) != player.allies.end()) {
                cout << "你們已經是盟友了！" << endl;
            } else {
                player.allies.push_back(targetCountry);
                target.allies.push_back(playerCountry);
                cout << "你與 " << targetCountry << " 建立了同盟關係！" << endl;
            }
            break;
        }
        case 2: {
            auto it = find(player.allies.begin(), player.allies.end(), targetCountry);
            if (it != player.allies.end()) {
                player.allies.erase(it);
                auto it2 = find(target.allies.begin(), target.allies.end(), playerCountry);
                if (it2 != target.allies.end()) {
                    target.allies.erase(it2);
                }
                cout << "你解除了與 " << targetCountry << " 的同盟關係。" << endl;
            } else {
                cout << "你們沒有同盟關係！" << endl;
            }
            break;
        }
        case 3: {
            int benefit = rand() % 10 + 5;
            player.economy = min(100, player.economy + benefit);
            target.economy = min(100, target.economy + benefit);
            cout << "你與 " << targetCountry << " 簽訂了貿易協定，雙方經濟各增長 " << benefit << " 點。" << endl;
            break;
        }
        case 4: {
            int benefit = rand() % 8 + 3;
            player.technology = min(100, player.technology + benefit);
            target.technology = min(100, target.technology + benefit);
            cout << "你與 " << targetCountry << " 進行了技術交流，雙方科技各增長 " << benefit << " 點。" << endl;
            break;
        }
        default:
            cout << "無效選擇！" << endl;
        }
    }

    void declareWar() {
        cout << "\n可宣戰的國家：" << endl;
        vector<string> otherCountries;

        for (const auto& pair : countries) {
            if (pair.first != playerCountry) {
                otherCountries.push_back(pair.first);
            }
        }

        for (int i = 0; i < otherCountries.size(); i++) {
            cout << i + 1 << ". " << otherCountries[i] << endl;
        }

        int choice;
        cout << "選擇宣戰國家 (1-9): ";
        cin >> choice;
        string targetCountry = otherCountries[choice - 1];

        Country& player = countries[playerCountry];
        Country& target = countries[targetCountry];

        if (find(player.enemies.begin(), player.enemies.end(), targetCountry) != player.enemies.end()) {
            cout << "你們已經處於戰爭狀態！" << endl;
            return;
        }

        auto it = find(player.allies.begin(), player.allies.end(), targetCountry);
        if (it != player.allies.end()) {
            player.allies.erase(it);
            auto it2 = find(target.allies.begin(), target.allies.end(), playerCountry);
            if (it2 != target.allies.end()) {
                target.allies.erase(it2);
            }
            cout << "你背叛了與 " << targetCountry << " 的同盟關係！" << endl;
        }

        cout << "\n===== 戰爭開始！" << playerCountry << " vs " << targetCountry << " =====" << endl;

        int playerPower = player.military * 2 + player.technology + player.economy;
        int targetPower = target.military * 2 + target.technology + target.economy;

        playerPower += rand() % 21 - 10;
        targetPower += rand() % 21 - 10;

        if (playerPower > targetPower) {
            cout << "你的軍隊取得了勝利！" << endl;

            int gain = rand() % 15 + 10;
            player.economy = min(100, player.economy + gain);
            player.military = min(100, player.military + gain/2);

            target.economy = max(0, target.economy - gain);
            target.military = max(0, target.military - gain);

            cout << "你獲得了 " << gain << " 點經濟資源和 " << gain/2 << " 點軍事資源。" << endl;

            player.enemies.push_back(targetCountry);
            target.enemies.push_back(playerCountry);
        } else {
            cout << "你的軍隊戰敗了！" << endl;

            int loss = rand() % 15 + 5;
            player.economy = max(0, player.economy - loss);
            player.military = max(0, player.military - loss);

            cout << "你損失了 " << loss << " 點經濟資源和 " << loss << " 點軍事資源。" << endl;

            player.enemies.push_back(targetCountry);
            target.enemies.push_back(playerCountry);
        }
    }

    void viewOtherCountries() {
        cout << "\n其他國家狀態：" << endl;
        for (const auto& pair : countries) {
            if (pair.first != playerCountry) {
                cout << pair.first << ": 經濟 " << pair.second.economy << ", 軍事 " << pair.second.military
                     << ", 科技 " << pair.second.technology << endl;
            }
        }
    }

    void simulateWorldEvents() {
        cout << "\n===== 世界新聞 =====" << endl;

        int numEvents = rand() % 3 + 1;

        for (int i = 0; i < numEvents; i++) {
            int eventType = rand() % 4;

            switch (eventType) {
            case 0: {
                string country = getRandomCountry();
                int loss = rand() % 20 + 10;
                countries[country].economy = max(0, countries[country].economy - loss);
                cout << country << " 遭遇經濟危機，經濟下降 " << loss << " 點。" << endl;
                break;
            }
            case 1: {
                string country = getRandomCountry();
                int gain = rand() % 15 + 5;
                countries[country].technology = min(100, countries[country].technology + gain);
                cout << country << " 取得科技突破，科技增長 " << gain << " 點。" << endl;
                break;
            }
            case 2: {
                string country1 = getRandomCountry();
                string country2;
                do {
                    country2 = getRandomCountry();
                } while (country1 == country2);

                cout << country1 << " 和 " << country2 << " 爆發戰爭！" << endl;

                if (find(countries[country1].enemies.begin(), countries[country1].enemies.end(), country2) == countries[country1].enemies.end()) {
                    countries[country1].enemies.push_back(country2);
                }
                if (find(countries[country2].enemies.begin(), countries[country2].enemies.end(), country1) == countries[country2].enemies.end()) {
                    countries[country2].enemies.push_back(country1);
                }
                break;
            }
            case 3: {
                string country1 = getRandomCountry();
                string country2;
                do {
                    country2 = getRandomCountry();
                } while (country1 == country2);

                cout << country1 << " 和 " << country2 << " 簽訂同盟條約！" << endl;

                if (find(countries[country1].allies.begin(), countries[country1].allies.end(), country2) == countries[country1].allies.end()) {
                    countries[country1].allies.push_back(country2);
                }
                if (find(countries[country2].allies.begin(), countries[country2].allies.end(), country1) == countries[country2].allies.end()) {
                    countries[country2].allies.push_back(country1);
                }
                break;
            }
            }
        }
    }

    string getRandomCountry() {
        auto it = countries.begin();
        advance(it, rand() % countries.size());
        return it->first;
    }

    void checkWinCondition() {
        Country& player = countries[playerCountry];

        if (player.economy <= 0 || player.military <= 0) {
            cout << "\n你的國家已經崩潰！遊戲結束。" << endl;
            gameOver = true;
            return;
        }

        int strongerCount = 0;
        for (const auto& pair : countries) {
            if (pair.first != playerCountry) {
                int otherPower = pair.second.economy + pair.second.military + pair.second.technology;
                int playerPower = player.economy + player.military + player.technology;

                if (playerPower > otherPower) {
                    strongerCount++;
                }
            }
        }

        if (strongerCount >= 8) {
            cout << "\n恭喜！你的國家已成為世界上最強大的國家！" << endl;
            gameOver = true;
        }
    }

    void endGame() {
        cout << "\n===== 遊戲結束 =====" << endl;
        cout << "最終年份: " << currentYear << endl;
        countries[playerCountry].displayStatus();

        cout << "\n===== 最終國家排名 =====" << endl;
        vector<pair<string, int>> rankings;

        for (const auto& pair : countries) {
            int power = pair.second.economy + pair.second.military + pair.second.technology;
            rankings.emplace_back(pair.first, power);
        }

        sort(rankings.begin(), rankings.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

        for (int i = 0; i < rankings.size(); i++) {
            cout << i + 1 << ". " << rankings[i].first << " (實力: " << rankings[i].second << ")" << endl;
        }

        cout << "\n感謝遊玩十國爭霸！" << endl;
    }
};

int main() {
    srand(time(0));
    WorldConquestGame game;
    game.startGame();
    return 0;
}