#include <iostream>
#include <cassert>
#include <vector>
#include <memory> //Для работы с умными указателями std::unique_ptr
#include <cmath>

//template<class T>

class Vector3D
{
private:
    float x_cordinate;
    float y_cordinate;
    float z_cordinate;
    float *vector_arr = nullptr;
    int Number_vector;

public:
    static inline unsigned counter_vector{}; // Счетчик созданных векторов
    static inline bool logical_value = false;

    Vector3D(float x_cordinate, float y_cordinate, float z_cordinate) //Конструктор с параметром.
    {
        this->x_cordinate = x_cordinate;
        this->y_cordinate = y_cordinate;
        this->z_cordinate = z_cordinate;
        this->vector_arr = new float[3]{x_cordinate, y_cordinate, z_cordinate};

        ++counter_vector;
        this->Number_vector = counter_vector;

        std::cout << "Vector Number " << Number_vector << " created" << std::endl;
    }
   Vector3D() //Конструктор по умолчанию.
   {
       x_cordinate=0;
       y_cordinate=0;
       z_cordinate=0;
       this->vector_arr = new float[3]{x_cordinate, y_cordinate, z_cordinate};

       ++counter_vector;
        this->Number_vector = counter_vector;

        std::cout << "Vector Number " << Number_vector << " created" << std::endl;
    }

    //Сеттеры для координат
    void set_x (float Value_x)
    {
        x_cordinate=Value_x;
        vector_arr[0] = x_cordinate;
    }

    void set_y (float Value_y)
    {
        y_cordinate=Value_y;
        vector_arr[1] = y_cordinate;
    }

    void set_z (float Value_z)
    {
        z_cordinate=Value_z;
        vector_arr[2] = z_cordinate;
    }

    //Геттеры для координат вектора
    float get_x () {return x_cordinate;}
    float get_y () {return y_cordinate;}
    float get_z () {return z_cordinate;}

    Vector3D(const Vector3D &copy_object) //Конструктор копирования
    {
        delete[] vector_arr; //Освобожденине динамический выделенной памяти
        vector_arr=new float[3]{};

        x_cordinate = copy_object.x_cordinate;
        y_cordinate = copy_object.y_cordinate;
        z_cordinate = copy_object.z_cordinate;
        vector_arr = new float[3]{x_cordinate, y_cordinate, z_cordinate};
         std::cout << "Vector " << copy_object.Number_vector << " copy in";
         ++counter_vector;
         Number_vector = counter_vector;
         std::cout << " Vector " << Number_vector << std::endl;

    }

    // Конструктор перемещения, который передаёт право собственности на move_object.vector_arr в vector_arr
    Vector3D(Vector3D && move_object) noexcept : vector_arr(move_object.vector_arr), x_cordinate(move_object.x_cordinate), y_cordinate(move_object.y_cordinate), z_cordinate(move_object.z_cordinate)
    {
        move_object.x_cordinate = 0;
        move_object.y_cordinate = 0;
        move_object.z_cordinate = 0;
        move_object.vector_arr = nullptr; // зануление указателя
        Number_vector = 0;
        std::cout << "Vector new move in ";
        Number_vector = counter_vector;
        std::cout << "Vector " << Number_vector << std::endl;
        logical_value = true;
    }
    // Оператор присваивания копированием, который выполняет глубокое копирование x.m_ptr в m_ptr
    Vector3D &operator=(const Vector3D &copy_object)
    {
        // Проверка на самоприсваивание
        if(&copy_object==this)
            return*this;

        // Удаляем всё, что к этому моменту может хранить указатель
        delete vector_arr;

        // Копируем передаваемый объект
        vector_arr=new float[3]{};
        x_cordinate=copy_object.x_cordinate;
        y_cordinate=copy_object.y_cordinate;
        z_cordinate=copy_object.z_cordinate;
        vector_arr=new float[3]{x_cordinate, y_cordinate, z_cordinate};

        std::cout << "Vector " << this->Number_vector;
        Number_vector = ++counter_vector;
        std::cout << " = Vector " << Number_vector << std:: endl;

        return*this;
    }

    // Оператор присваивания перемещением
    Vector3D &operator=(Vector3D &&copy_object)
    {
        // Проверка на самоприсваивание
        if(&copy_object==this)
            return*this;

        // Удаляем всё, что к этому моменту может хранить указатель
        delete[] vector_arr;

        // Копируем передаваемый объект
        vector_arr=new float[3]{};
        x_cordinate=copy_object.x_cordinate;
        y_cordinate=copy_object.y_cordinate;
        z_cordinate=copy_object.z_cordinate;
        vector_arr= new float[3]{x_cordinate, y_cordinate, z_cordinate};

        std::cout << "Vector " << this->Number_vector;
        Number_vector = ++counter_vector;
        std::cout << " =&move Vector " << Number_vector << std:: endl;

        return*this;
    }


    ~Vector3D()  //Деструктор (выводит информацию об удалении объектов).
    {
        delete[] vector_arr; //Освобожденине динамический выделенной памяти
        vector_arr = nullptr; //Зануление указателя
        if (logical_value == false) //Если был испол. констр. перемещ., то в консоль не вывыдется инф. об удалении вектора
        {
            std::cout << "DELETE Vector Number " << this->Number_vector  << std::endl;
        }
        
        logical_value = false;
    }

    void print()
    {
        for (int i = 0; i < 3; i++)
        {
            std::cout<< vector_arr[i] << " ";
        }

        std::cout <<"    Number of Vector " << Number_vector << std::endl;
    }
};

/*Класс Vector2D создан для того, чтобы на его примере реализовать умные указатели, по своей
концепции идентичен классу Vector3D*/
class Vector2D
{
private:
    float x_cordinate;
    float y_cordinate;
    std::unique_ptr<float[]> vector_arr {std::make_unique<float[]>(2)};
    int Number_vector;

public:
    static inline unsigned counter_vector_2D{}; // Счетчик созданных векторов
    static inline bool logical_value_2D = false;

    //Геттеры для координат вектора
    float get_x () {return x_cordinate;}
    float get_y () {return y_cordinate;}

    Vector2D(float x_cordinate, float y_cordinate) //Конструктор с параметром.
    {
        this->x_cordinate = x_cordinate;
        this->y_cordinate = y_cordinate;
        
        //Присвоение соответсвующих координат умному указателю
        this->vector_arr[0] =x_cordinate;
        this->vector_arr[1] = y_cordinate;
        
        ++counter_vector_2D;
        this->Number_vector = counter_vector_2D;

        std::cout << "Vector 2D Number " << Number_vector << " created" << std::endl;
    }
   Vector2D() //Конструктор по умолчанию.
   {
       x_cordinate=0;
       y_cordinate=0;

       //Вектор инициализирован нулями по умолчанию

       ++counter_vector_2D;
       this->Number_vector = counter_vector_2D;

       std::cout << "Vector 2D Number " << Number_vector << " created" << std::endl;
    }

    Vector2D(const Vector2D &copy_object) //Конструктор копирования
    {
        x_cordinate = copy_object.x_cordinate;
        y_cordinate = copy_object.y_cordinate;
        vector_arr[0] =x_cordinate;
        vector_arr[1] = y_cordinate;
         std::cout << "Vector 2D " << copy_object.Number_vector << " copy in";
         ++counter_vector_2D;
         Number_vector = counter_vector_2D;
         std::cout << " Vector 2D " << Number_vector << std::endl;
    }

    // Конструктор перемещения, который передаёт право собственности на move_object.vector_arr в vector_arr
    Vector2D(Vector2D && move_object) noexcept : x_cordinate(move_object.x_cordinate), y_cordinate(move_object.y_cordinate)
    {
        move_object.x_cordinate = 0;
        move_object.y_cordinate = 0;
        Number_vector = 0;

        vector_arr[0] =x_cordinate;
        vector_arr[1] = y_cordinate;

        std::cout << "Vector new move in ";
        Number_vector = counter_vector_2D;
        std::cout << "Vector " << Number_vector << std::endl;
        logical_value_2D = true;
    }

    // Оператор присваивания копированием, который выполняет глубокое копирование x.m_ptr в m_ptr
    Vector2D &operator=(const Vector2D &copy_object)
    {
        // Проверка на самоприсваивание
        if(&copy_object==this)
            return*this;

        // Копируем передаваемый объект
        x_cordinate=copy_object.x_cordinate;
        y_cordinate=copy_object.y_cordinate;
        vector_arr[0] =x_cordinate;
        vector_arr[1] = y_cordinate;

        std::cout << "Vector 2D " << this->Number_vector;
        Number_vector = ++counter_vector_2D;
        std::cout << " = Vector " << Number_vector << std:: endl;

        return*this;
    }

    // Оператор присваивания перемещением
    Vector2D &operator=(Vector2D &&copy_object)
    {
        // Проверка на самоприсваивание
        if(&copy_object==this)
            return*this;

        // Копируем передаваемый объект
        x_cordinate=copy_object.x_cordinate;
        y_cordinate=copy_object.y_cordinate;
        vector_arr[0] =x_cordinate;
        vector_arr[1] = y_cordinate;

        std::cout << "Vector " << this->Number_vector;
        Number_vector = ++counter_vector_2D;
        std::cout << " =&move Vector " << Number_vector << std:: endl;

        return*this;
    }

   ~Vector2D()  //Деструктор (выводит информацию об удалении объектов).
    {
        std::cout << "DELETE Vector 2D Number " << this->Number_vector << std::endl;
    }

    void print()
    {
        for (int i = 0; i < 2; i++)
        {
            std::cout<< this->vector_arr[i] << " ";
        }
        
        std::cout << std::endl;
    }
};

/*Функция для создания обратного вектора создан для демонстрации работы конструктора перемещения*/
float *inversion_vector3D(Vector3D object)
{
    float *inverse = new float[3] {-object.get_x(), -object.get_y(), -object.get_z()};
    return inverse;
};

float *normal_function (std::shared_ptr<Vector2D> const &normal_object)
{   
    std::shared_ptr<Vector2D> function_vector (normal_object);
    std::cout<< "Use Function and creted new shared_ptr" << std::endl;
    std::cout << "Number of shared_ptr = " <<function_vector.use_count() << std::endl;
    
    float variable = sqrtf ((function_vector -> get_x())*(function_vector -> get_x()) + (function_vector -> get_y())*(function_vector -> get_y()));
    float *normal_vector = new float[2] {(function_vector->get_x())/variable, (function_vector->get_y())/variable};
    
    std::cout << "Exit function and delete one shered_ptr" << std::endl;

    return normal_vector;
}

int main ()
{
    std::cout << "------- Simple construction - First Vector ------" << std::endl;
    Vector3D one {10, 20, 30};
	one.print();
    
    std::cout << "------- Construction po umolchaniu - Second Vector ------" << std::endl;
    Vector3D two;
    two.print();

    std::cout << "------- Simple Copy - third Vector ------" << std::endl;
    Vector3D three {one};
    three.print();

    std::cout << "------- Operator ravno - fourth Vector ------" << std::endl;
    Vector3D four = one;
    four.print();
    
    std::cout << "------- Construction Move - five Vector ------" << std::endl;
    Vector3D five (std::move(Vector3D {1, 2, 3}));
    five.print();

    std::cout << "------- Use Function inverse Vector ------" << std::endl;
    float *inv_six = inversion_vector3D(std::move(Vector3D {1, 2, 3}));
    std::cout << "inverse vector = " << inv_six[0] << " "<< inv_six[1] << " " << inv_six[2] << std::endl;

    std::cout << "------- Operator Move and = ------" << std::endl;
    Vector3D seven = std::move(Vector3D(10, 20, 30));
    seven.print();

    /*Дальнейшая часть программы посвящена тестированию умных указателей для класса вектора 2D*/
    std::cout << "----------------------------------" << std::endl;
    std::cout << "USE UNIQE PTR for class Vector 2D" << std::endl;
    std::cout << "----------------------------------" << std::endl;

    //Инициализация экземпляра класса с умными указателями
    std::cout << "------- Simple construction - First Vector ------" << std::endl;
    Vector2D eight {0.1, 2}; //Вектор 2D 1
    eight.print();

    //Инициализация экземпляра класса с умными указателями конструктором по умолчанию
    std::cout << "------- Construction po umolchaniu - Second Vector ------" << std::endl;
    Vector2D nine {}; //Вектор 2D 2
    nine.print();

    std::cout << "------- Simple Copy - third Vector ------" << std::endl;
    Vector2D ten {eight}; //вектор 2D 3
    ten.print();

    std::cout << "------- Operator ravno - fourth Vector ------" << std::endl;
    Vector2D eleven = eight;
    eleven.print();

    std::cout << "------- Construction Move - five Vector ------" << std::endl;
    Vector2D twelve (std::move(Vector2D {2, 3}));
    twelve.print();

    std::cout << "------- Operator Move and = ------" << std::endl;
    Vector2D thirteen = std::move(Vector2D(10, 20));
    thirteen.print();

    //Иллюстрация рабты умных указателей shared_ptr
    std::cout << "Created new shared_ptr - fourteen" << std::endl;
    //Создаем новый умный указатель shared_ptr
    std::shared_ptr<Vector2D> fourteen = std::make_shared<Vector2D> (3, 4);
    std::cout << "Number of shared_ptr = " <<fourteen.use_count() << std::endl;

    std::cout << "New example of shared_ptr - fourteen" << std::endl;
    //Повторно используем ранее созданный умный указатель shared_ptr
    std::shared_ptr<Vector2D> fiveteen (fourteen);
    std::cout << "Number of shared_ptr = " <<fourteen.use_count() << std::endl;

    std::cout << "Use function normalization" << std::endl;
    //Используем Создаем умный указатель shared_ptr для работы с функцией
    float *sixteen = normal_function (fourteen);

    std::cout << "Print normalization fourteen: ";
    std::cout << sixteen[0] << "  " << sixteen[1] << std::endl;

	return 0;
}