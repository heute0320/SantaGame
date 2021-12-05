#define _CRT_SECURE_NO_WARNINGS

#include <bangtal>
#include <bangtal.h>
#include <cstring>
#include <cstdio>
#include <ctime>

using namespace bangtal;

// 배경화면 설정
ScenePtr scene;

// 목표물 구조체
struct Target
{
    int num;
    ObjectPtr tarObj;
};


// 목표물 객체 생성
Target Rudolph;
Target Gift;
Target House1;
Target House2;
Target House3;
Target House4;
Target House5;


int main(void)
{
    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

    // 시작화면 생성
    scene = Scene::create("Santa Game", "image/back1.png");
    
    // 게임 시작 소개글
    showMessage("크리스마스 시즌에 가장 바쁜 이들이 있는데. 바로 산타들이다. \n\
그런데, 올해 산타 한명이 감기에 걸려 일일 산타를 1명 뽑는다고 한다.\n\
근무시간은 6시간, 시급은 무려 100만원이다.");
    
    auto game1_hide_timer = Timer::create(1);// 게임1에서 루돌프가 안나오는 시간을 재는 타이머
    auto game1_show_timer = Timer::create(1);// 게임1에서 루돌프가 나오는 시간을 재는 타이머
    // 게임2에서 5초 제한을 보여주는 타이머
    auto game2Timer = Timer::create(10);

    // 시작 버튼 객체
    auto startButton = Object::create("image/yes.png", scene, 165, 280, false);
    startButton->setScale(0.25f);
    // 종료 버튼 객체
    auto endButton = Object::create("image/no.png", scene, 1010, 280, false);
    endButton->setScale(0.25f);

    // 다음 장면을 이동시키는 버튼 객체
    auto click1 = Object::create("image/click.png", scene, 1110, 705);
    click1->setScale(0.2f);
    auto click2 = Object::create("image/click.png", scene, 1110, 705, false);
    click2->setScale(0.2f);
    auto click3 = Object::create("image/click.png", scene, 1110, 705, false);
    click3->setScale(0.2f);
    auto click4 = Object::create("image/click.png", scene, 1110, 705, false);
    click4->setScale(0.2f);
    auto click5 = Object::create("image/click.png", scene, 1110, 705, false);
    click5->setScale(0.2f);
    auto click6 = Object::create("image/click.png", scene, 1110, 705, false);
    click6->setScale(0.2f);
    auto click7 = Object::create("image/click.png", scene, 1110, 705, false);
    click7->setScale(0.2f);
    auto click8 = Object::create("image/click.png", scene, 1110, 705, false);
    click8->setScale(0.2f);
    auto click9 = Object::create("image/click.png", scene, 1110, 705, false);
    click9->setScale(0.2f);

    // 루돌프 객체 
    Rudolph.tarObj = Object::create("image/r1.png", scene, 0, 0, false);
    // 선물 객체
    Gift.tarObj = Object::create("image/p01.png", scene, 0, 0, false);
    // 집 객체
    House1.tarObj = Object::create("image/h01.png", scene, 240, 200, false);
    House1.tarObj->setScale(0.9f);
    House2.tarObj = Object::create("image/h02.png", scene, 730, 150, false);
    House2.tarObj->setScale(0.7f);
    House3.tarObj = Object::create("image/h03.png", scene, 1020, 180, false);
    House3.tarObj->setScale(0.9f);
    House4.tarObj = Object::create("image/h04.png", scene, 0, 250, false);
    House4.tarObj->setScale(1.2f);
    House5.tarObj = Object::create("image/h05.png", scene, 450, 170, false);
    House5.tarObj->setScale(1.0f);

    // 10초 제한 시간이 끝나면 종료 이미지가 나오고, 재시작을 할 수 있게 해준다.
    game2Timer->setOnTimerCallback([&](TimerPtr t)->bool {
        scene->setImage("image/back2.png");
        showMessage("실패했군! 다시 도전하겠나?");
        game2Timer->stop();
        game2Timer->set(15);
        hideTimer();
        startButton->show();
        endButton->show();
        Gift.tarObj->hide();
        return true;
        });

    // 루돌프를 클릭하면 다음으로 넘어간다. 
    Rudolph.tarObj->setOnMouseCallback([&](auto object, auto x, auto y, auto action)->bool {
        Rudolph.num += 1;
        if (Rudolph.num >= 1) {
            game1_hide_timer->stop();
            game1_show_timer->stop();
            Rudolph.tarObj->hide();
            click3->show();
        };
        return true;
        });

    // 선물을 클릭하면 이동한다.
    Gift.tarObj->setOnMouseCallback([&](auto object, auto x, auto y, auto action)->bool {
        if (Gift.num < 10) {
            Gift.num += 1;
            Gift.tarObj->locate(scene, rand() % 700 + 200, rand() % 550 + 150);
            Gift.tarObj->setImage("image/p0" + std::to_string(Gift.num % 5 + 1) + ".png");
            if (Gift.num >= 5) {
                Gift.num = 0;
                Gift.tarObj->hide();
                game2Timer->stop();
                click6->show();
            }
        }
     
        return true;
        });


    House1.tarObj->setOnMouseCallback([&](auto object, auto x, auto y, auto action)->bool {
        if (Gift.num % 5 + 1 == 1) {
            Gift.num += 1;
            Gift.tarObj->setImage("image/p0" + std::to_string(Gift.num % 5 + 1) + ".png");
            if (Gift.num >= 20) {
                Gift.tarObj->hide();
                click9->show();
            }
        }
        return true;
        });
    House2.tarObj->setOnMouseCallback([&](auto object, auto x, auto y, auto action)->bool {
        if (Gift.num % 5 + 1 == 2) {
            Gift.num += 1;
            Gift.tarObj->setImage("image/p0" + std::to_string(Gift.num % 5 + 1) + ".png");
            if (Gift.num >= 20) {
                Gift.tarObj->hide();
                click9->show();
            }
        }
        return true;
        });
    House3.tarObj->setOnMouseCallback([&](auto object, auto x, auto y, auto action)->bool {
        if (Gift.num % 5 + 1 == 3) {
            Gift.num += 1;
            Gift.tarObj->setImage("image/p0" + std::to_string(Gift.num % 5 + 1) + ".png");
            if (Gift.num >= 20) {
                Gift.tarObj->hide();
                click9->show();
            }
        }
        return true;
        });
    House4.tarObj->setOnMouseCallback([&](auto object, auto x, auto y, auto action)->bool {
        if (Gift.num % 5 + 1 == 4) {
            Gift.num += 1;
            Gift.tarObj->setImage("image/p0" + std::to_string(Gift.num % 5 + 1) + ".png");
            if (Gift.num >= 20) {
                Gift.tarObj->hide();
                click9->show();
            }
        }
        return true;
        });
    House5.tarObj->setOnMouseCallback([&](auto object, auto x, auto y, auto action)->bool {
        if (Gift.num % 5 + 1 == 5) {
            Gift.num += 1;
            Gift.tarObj->setImage("image/p0" + std::to_string(Gift.num % 5 + 1) + ".png");
            if (Gift.num >= 20) {
                Gift.tarObj->hide();
                click9->show();
            }
        }
        return true;
        });

    // 클릭 버튼을 누르면 적합한 화면으로 넘어간다. 
    click1->setOnMouseCallback([&](auto object, auto x, auto y, auto action)->bool {
        click1->hide();
        scene->setImage("image/back2.png");
        showMessage("도전 하겠는가?");
        startButton->show();
        endButton->show();
        return true;
        });

    click2->setOnMouseCallback([&](auto object, auto x, auto y, auto action)->bool {
        Rudolph.tarObj->show();
        Rudolph.tarObj->setScale(0.1f);
        click2->hide();
        scene->setImage("image/back4.png");
        //fullTimer->start();
        game1_show_timer->start();
        return true;
        });

    click3->setOnMouseCallback([&](auto object, auto x, auto y, auto action)->bool {
        click3->hide();
        scene->setImage("image/back5.png");
        showMessage("성공! 당신은 루돌프와 함께 배달할 수 있는 능력을 인정받았다.");
        click4->show();
        return true;
        });

    click4->setOnMouseCallback([&](auto object, auto x, auto y, auto action)->bool {
        click4->hide();
        scene->setImage("image/back6.png");
        showMessage("우와 축하해~ 첫번째 게임을 통화했구나! 나는 눈사람 조교2야.\n\
두 번째 테스트에서는 배달할 선물을 빠르게 획득하는 능력을 평가할거야.\n\
하늘에서 떨어지는 선물상자를 위에 보이는 제한 시간 내로 클릭하면 돼.");
        showTimer(game2Timer);
        click5->show();
        return true;
        });

    click5->setOnMouseCallback([&](auto object, auto x, auto y, auto action)->bool {
        showTimer(game2Timer);
        game2Timer->start();
        Gift.num = 0;
        Gift.tarObj->show();
        Gift.tarObj->setScale(0.4f);
        click5->hide();
        scene->setImage("image/back7.png");
        Gift.tarObj->locate(scene, rand() % (800 - 20) + 100, rand() % (580 - 20) + 80);

        return true;
        });

    click6->setOnMouseCallback([&](auto object, auto x, auto y, auto action)->bool {
        hideTimer();
        click6->hide();
        scene->setImage("image/back8.png");
        showMessage("성공! 루돌프와 선물 모두 획득했어:)");
        click7->show();
        return true;
        });

    click7->setOnMouseCallback([&](auto object, auto x, auto y, auto action)->bool {
        click7->hide();
        scene->setImage("image/back9.png");
        showMessage("수고 많았어. 마지막 테스트에서는 너의 배달 능력을 평가할거야.\n\
선물을 보고 배달할 집을 찾을 수 있는지 알아보는 테스트야.\n\
이번엔 내가 특별히 힌트를 줄게. 힌트는 ‘선물 상자 색깔’이야.");
        click8->show();
        return true;
        });

    click8->setOnMouseCallback([&](auto object, auto x, auto y, auto action)->bool {
        click8->hide();
        scene->setImage("image/back10.png");
        showMessage("화면에 보이는 선물 상자를 배달할 집을 선택하라.");
        Gift.num = 10;
        Gift.tarObj->show();
        Gift.tarObj->setImage("image/p0" + std::to_string(Gift.num%5+1) + ".png");
        Gift.tarObj->setScale(0.5f);
        Gift.tarObj->locate(scene, 600, 700);
        House1.tarObj->show();
        House2.tarObj->show();
        House3.tarObj->show();
        House4.tarObj->show();
        House5.tarObj->show();
        return true;
        });

    click9->setOnMouseCallback([&](auto object, auto x, auto y, auto action)->bool {
        House1.tarObj->hide();
        House2.tarObj->hide();
        House3.tarObj->hide();
        House4.tarObj->hide();
        House5.tarObj->hide();
        Gift.tarObj->hide();
        click9->hide();
        scene->setImage("image/back11.png");
        showMessage("일일 산타가 된 걸 축하해!!\n\
12월 24일 오후 2시까지 산타 마을 관리센터로 와!!");
        endButton->setImage("image/end.png");
        endButton->locate(scene, 600, 700);
        endButton->setScale(0.4f);
        endButton->show();
        return true;
        });


    // 게임1에서, 루돌프는 0.1초 내로 안나오다가, 나온 후 1초 이내로 사라진다.
    // 루돌프가 나오는 위치는 화면 내에서 난수로 결정된다.
    game1_hide_timer->setOnTimerCallback([&](TimerPtr t)->bool {
        Rudolph.tarObj->hide();
        game1_show_timer->set(rand() % 5 / 10);
        game1_show_timer->start();
        game1_hide_timer->stop();
        return true;
        });

    game1_show_timer->setOnTimerCallback([&](TimerPtr t)->bool {
        game1_hide_timer->set(rand() % 15 / 10);
        game1_hide_timer->start();
        game1_show_timer->stop();
        Rudolph.tarObj->show();
        Rudolph.tarObj->locate(scene, rand() % 1000 + 150, rand() % 600 + 150);
        return true;
        });

    // 시작 버튼을 누르면 게임이 시작된다. 
    startButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action) -> bool
        {
            startButton->hide();
            endButton->hide();
            scene->setImage("image/back3.png");
            showMessage("안녕. 나는 눈사람 조교1이야. 눈사람 조교는 게임을 설명해주는 역할을 하고 있어.\n\
첫 번째 테스트는 ‘루돌프 잡기’야. 화면 속 루돌프를 클릭해줘. 제한 시간은 없어.\n\
산타에게 루돌프는 꼭 필요한 존재야. 최선을 다해줘!");
            click2->show();
            return true;
        });

    // 게임 종료를 누르면 게임이 끝난다. 
    endButton->setOnMouseCallback([&](auto object, auto x, auto y, auto action)->bool {
        endGame();
        return true;
        });

    // 게임 시작
    startGame(scene);

    return 0;
}
