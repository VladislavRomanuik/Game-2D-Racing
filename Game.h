// ---------------------------------------------------------------------------
// модуль GameH
#ifndef GameH
#define GameH
// подключаем главную форму
#include "Main.h"
// ---------------------------------------------------------------------------

// класс игровые объекты (класс есть базовым для всех игровых объектов, то есть от него наслудеются классы PlayerCar, CarOpponent, Bonus)
class GameObject {
	// protected секция, то есть защищенная секция, секция видна классам насследникам
protected:
	// свойство картинка
	// TImage* im;
	// строка нахождения файла с картинкой
	AnsiString path;

	// private секция, то есть закрытая секция, к ней можно обращаться только ВНУТРИ КЛАССА GAMEOBJECT
private:
	// переменные координаты объектов (поля класса)
	int xLeft; // левый x
	int xRight; // правый x
	int yTop; // верхний y
	int yBottom; // нижний y

	// public секция, то есть к этим переменным/функциям имеется доступ везде, в любой строчке
public:
	TImage* im;
	int typeBonus;
	// координаты для смещения объектов
	int newCoord;

	// конструктор класса по умолчанию!!!!
	GameObject() {
		// присваиваем дефолтное значение координатам
		typeBonus = 0; // тип бонуса
		newCoord = 0;
		// новая координата, для дорог, бонуса, машинок оппонентов - ЭТО СМЕЩЕНИЕ ВНИЗ, ДЛЯ ИГРОКА - ЛЕВО, ПРАВО
		xLeft = 0; // левый x
		xRight = 0; // правый x
		yTop = 0; // верхний y
		yBottom = 0; // нижний y
	}

	// КОНСТРУКТОР КЛАССА УДАЛЯЕТ ВСЕ УКАЗАТЕЛИ, ВСЕГДА БЕЗ ПАРАМЕТРОВ
	~GameObject() {
		// УДВЛЯЕМ УКАЗАТЕЛЬ НА КАРТИНКУ (КАРТИНКУ)
		delete im;
	}
	// функции класса, ЗДЕСЬ ОПИСАНЫ ТОЛЬКО ПРОТОТИПЫ ФУНКЦИИ (прототипы это их оболочка - название и их параметр)
	// int/ void - тип вовращаемого значения функции
	// функция возвращает целое число (правый Х возвращает)
	int GetRightX();
	// функция возвращает целое число (левый Х возвращает)
	int GetLeftX();
	// функция возвращает целое число (верхний Y возвращает)
	int GetTopY();
	// функция возвращает целое число (нижний Y возвращает)
	int GetBottomY();
	// void - ничего не возвращает!!!
	// функции с параметром, которые устанавливают цифру координат
	void SetLeftX(int xLeft);
	void SetRightX(int xRight);
	void SetTopY(int yTop);
	void SetBottomY(int yBottom);

	// виртуальная функция(функция, которая наследуется и ее можно переопределять)
	// функция отрисовки объектов
	virtual void DrawObj(int newXLeft) {
	}
};

// класс Машинка Игрока, наследуется от базового класса GameObject
class PlayerCar : public GameObject {
	// public секция, то есть к этим переменным/функциям имеется доступ везде, в любой строчке
public:
	// конструктор класса
	PlayerCar() {
		// устанавливаем путь картинки
		path = "D:\\Машинки\\Win32\\Debug\\Car1.png";
		// создаем новую картинку, в скобочках параметр конструктора, то есть форма, где будет отображаться КАРТИНКА!!!
		im = new TImage(GameForm);
		im->Width = 75; // ширина картинки
		im->Height = 100; // высота картинки
		im->Left = 255; // левая координата по иксу
		im->Top = 800; // координата верха картинки
		im->Picture->LoadFromFile(path);
		// загружаем саму картинку с файла указанного пути
		SetLeftX(im->Left); // устанавливаем левый икс
		SetRightX(im->Left + im->Width); // устанавливаем правый икс
		SetTopY(im->Top); // устанавливаем верхний Y
		SetBottomY(im->Top + im->Height); // устанавливаем нижний У
		im->Parent = GameForm;
		// форма на которой будет картинка (родитель картинки)
	}
	// переопределенная функция отрисовки Машинки с параметрой новой координаты картинки (ПРОТОТИП)
	void DrawObj(int newXLeft);
};

// Класс Дорога, наследуется от базового GameObject
class Road : public GameObject {
	// public секция, то есть к этим переменным/функциям имеется доступ везде, в любой строчке
public:
	// конструктор класса
	Road(int TopY) {
		// устанавливаем путь картинки
		// СМОТРИ СТРОЧКУ 70, ТАМ ВСЕ ТАК ЖЕ!!!!!
		path = "D:\\Машинки\\Win32\\Debug\\Road.png";
		im = new TImage(GameForm); // СМОТРИ СТРОЧКУ 70, ТАМ ВСЕ ТАК ЖЕ!!!!!
		im->Width = 508;
		im->Height = 408;
		im->Left = 200; // СМОТРИ СТРОЧКУ 70, ТАМ ВСЕ ТАК ЖЕ!!!!!
		im->Top = TopY;
		im->Stretch = true;
		// im->Proportional = true;
		im->Picture->LoadFromFile(path);
		SetLeftX(im->Left);
		SetRightX(im->Left + im->Width);
		SetTopY(im->Top); // СМОТРИ СТРОЧКУ 70, ТАМ ВСЕ ТАК ЖЕ!!!!!
		SetBottomY(im->Top + im->Height);
		im->Parent = GameForm;
		// СМОТРИ СТРОЧКУ 70, ТАМ ВСЕ ТАК ЖЕ!!!!!
	}
	// переопределенная функция отрисовки Дороги с параметрой новой координаты картинки (ПРОТОТИП)
	void DrawObj(int newTopY);
};

// класс Машинок противников, наследуется от базового класса GameObject
class OpponentCar : public GameObject {
	// public секция, то есть к этим переменным/функциям имеется доступ везде, в любой строчке
public:
	// конструктор класса
	OpponentCar(int LeftX, int TopY, int typeCar) {
		// устанавливаем путь картинки
		// СМОТРИ СТРОЧКУ 70, ТАМ ВСЕ ТАК ЖЕ!!!!!
		path = "D:\\Машинки\\Win32\\Debug\\Car";
		path += typeCar;
		path += ".png";
		im = new TImage(GameForm); // СМОТРИ СТРОЧКУ 70, ТАМ ВСЕ ТАК ЖЕ!!!!!
		im->Width = 75;
		im->Height = 100;
		im->Left = LeftX; // СМОТРИ СТРОЧКУ 70, ТАМ ВСЕ ТАК ЖЕ!!!!!
		im->Top = TopY;
		im->Picture->LoadFromFile(path);
		// СМОТРИ СТРОЧКУ 70, ТАМ ВСЕ ТАК ЖЕ!!!!!
		SetLeftX(im->Left);
		SetRightX(im->Left + im->Width);
		SetTopY(im->Top);
		SetBottomY(im->Top + im->Height);
		// СМОТРИ СТРОЧКУ 70, ТАМ ВСЕ ТАК ЖЕ!!!!!
		im->Parent = GameForm; // СМОТРИ СТРОЧКУ 70, ТАМ ВСЕ ТАК ЖЕ!!!!!
	}
	// переопределенная функция отрисовки Машинки Опонента с параметрой новой координаты картинки (ПРОТОТИП)
	void DrawObj(int newTopY);
};

// класс Бонус, наследуется от базового класса GameObject
class Bonus : public GameObject {
	// public секция, то есть к этим переменным/функциям имеется доступ везде, в любой строчке
public:
	// тип бонуса, по которому будет узнаваться вид бонуса и его свойства
	// int typeBonus;
	// конструктор класса с параметрами
	Bonus(int LeftX, int TopY, int typeBonus_) {
		typeBonus = typeBonus_;
		path = "D:\\Машинки\\Win32\\Debug\\Bonus";
		path += typeBonus;
		path += ".png";
		im = new TImage(GameForm); // СМОТРИ СТРОЧКУ 70, ТАМ ВСЕ ТАК ЖЕ!!!!!
		im->Width = 50;
		im->Height = 50;
		im->Left = LeftX; // СМОТРИ СТРОЧКУ 70, ТАМ ВСЕ ТАК ЖЕ!!!!!
		im->Top = TopY;
		im->Stretch = true;
		// LeftOpponentCar = LeftX;
		// im->Proportional = true;
		im->Picture->LoadFromFile(path);
		// СМОТРИ СТРОЧКУ 70, ТАМ ВСЕ ТАК ЖЕ!!!!!
		SetLeftX(im->Left);
		SetRightX(im->Left + im->Width);
		SetTopY(im->Top);
		SetBottomY(im->Top + im->Height);
		// СМОТРИ СТРОЧКУ 70, ТАМ ВСЕ ТАК ЖЕ!!!!!
		im->Parent = GameForm; // СМОТРИ СТРОЧКУ 70, ТАМ ВСЕ ТАК ЖЕ!!!!!
	}
	// переопределенная функция отрисовки Бонуса с параметрой новой координаты картинки (ПРОТОТИП)
	void DrawObj(int newTopY);
};

// класс, который будет обрабатывать все события игры
class Game {
	// public секция, то есть к этим переменным/функциям имеется доступ везде, в любой строчке
public:
	bool game_;
	bool immortality;
	// массив GameObject
	GameObject* gameObject[12];

	// конструктор класса по умолчанию, создаем объекты
	Game() {
		game_ = false;
		immortality = false;
		// выделяем память под каждый объект
		// Память под 1 кусок дороги
		gameObject[1] = new Road(-100);
		// Память под 2 кусок дороги
		gameObject[2] = new Road(300);
		// Память под 3 кусок дороги
		gameObject[3] = new Road(700);
		// // Память под 4 кусок дороги
		gameObject[4] = new Road(800);
		// Память под машинку игрока
		gameObject[0] = new PlayerCar();
		// Память под машинку противника
		gameObject[5] = new OpponentCar(300, -100, 1);
		// Память под машинку противника
		gameObject[6] = new OpponentCar(300, -100, 1);
		// Память под машинку противника
		gameObject[7] = new OpponentCar(300, -100, 1);
		// Память под бонус
		gameObject[8] = new Bonus(300, 100, 1);
	}

	// КОНСТРУКТОР КЛАССА, УДАЛЯЕМ УКАЗАТЕЛИ НА ИГРОВЫЕ ОБЪЕКТЫ
	~Game() {
		// перебор в цыкле всех объектов
		for (int i = 0; i < 9; i++) {
			// проверка на пустоту
			if (gameObject[i] != NULL) {
				// удаляем игровые объекты
				delete gameObject[i];
			}
		}
	}
	// Сам Игровой процесс, с ПАРАМЕТРОМ -  int speedcar - параметр
	void GamePlay(int speedCar);
	// Действие бонуса
	void BonusActive();
};

#endif
