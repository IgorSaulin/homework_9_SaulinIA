#include <iostream>
#include <cassert>
#include <vector>
#include <memory> //Для работы с умными указателями std::unique_ptr
#include <cmath>

class Vector3D
{
private:
    float x_cordinate;
    float y_cordinate;
    float z_cordinate;
    std::unique_ptr<float[]> vector_arr {std::make_unique<float[]>(3)};
    int Number_vector;

public:
    static inline unsigned counter_vector{}; // Счетчик созданных векторов
    static inline bool logical_value = false;

    Vector3D(float x_cordinate, float y_cordinate, float z_cordinate) //Конструктор с параметром.
    {
        this->x_cordinate = x_cordinate;
        this->y_cordinate = y_cordinate;
        this->z_cordinate = z_cordinate;

        this->vector_arr[0] = x_cordinate;
        this->vector_arr[1] = y_cordinate;
        this->vector_arr[2] = z_cordinate;

        ++counter_vector;
        this->Number_vector = counter_vector;

        std::cout << "Vector Number " << Number_vector << " created" << std::endl;
    }
   Vector3D() //Конструктор по умолчанию.
   {
       x_cordinate=0;
       y_cordinate=0;
       z_cordinate=0;

       //Вектор по умолчанию инициализируется нулями
       ++counter_vector;
        this->Number_vector = counter_vector;

        std::cout << "Vector Number " << Number_vector << " created" << std::endl;
    }
    
    //Сеттеры для координат
    void set_x (float Value_x)
    {
        x_cordinate=Value_x;
        this->vector_arr[0] = x_cordinate;
    }

    void set_y (float Value_y)
    {
        y_cordinate=Value_y;
        this->vector_arr[1] = y_cordinate;
    }

    void set_z (float Value_z)
    {
        z_cordinate=Value_z;
        this->vector_arr[2] = z_cordinate;
    }

    //Геттеры для координат вектора
    float get_x () {return x_cordinate;}
    float get_y () {return y_cordinate;}
    float get_z () {return z_cordinate;}
    
    Vector3D(const Vector3D &copy_object) //Конструктор копирования
    {
        x_cordinate = copy_object.x_cordinate;
        y_cordinate = copy_object.y_cordinate;
        z_cordinate = copy_object.z_cordinate;
        
        this->vector_arr[0] = x_cordinate;
        this->vector_arr[1] = y_cordinate;
        this->vector_arr[2] = z_cordinate;

         std::cout << "Vector " << copy_object.Number_vector << " copy in";
         ++counter_vector;
         Number_vector = counter_vector;
         std::cout << " Vector " << Number_vector << std::endl;

    }
    
    // Конструктор перемещения, который передаёт право собственности на move_object.vector_arr в vector_arr
    Vector3D(Vector3D && move_object) noexcept : x_cordinate(move_object.x_cordinate), y_cordinate(move_object.y_cordinate), z_cordinate(move_object.z_cordinate)
    {
        move_object.x_cordinate = 0;
        move_object.y_cordinate = 0;
        move_object.z_cordinate = 0;
        Number_vector = 0;

        vector_arr[0] = x_cordinate;
        vector_arr[1] = y_cordinate;
        vector_arr[2] = z_cordinate;

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

        // Копируем передаваемый объект
        x_cordinate=copy_object.x_cordinate;
        y_cordinate=copy_object.y_cordinate;
        z_cordinate=copy_object.z_cordinate;
        
        vector_arr[0] = x_cordinate;
        vector_arr[1] = y_cordinate;
        vector_arr[2] = z_cordinate;

        std::cout << "Vector " << this->Number_vector;
        
        std::cout << " = Vector " << copy_object.Number_vector << std:: endl;

        return*this;
    }
    
    // Оператор присваивания перемещением
    Vector3D &operator=(Vector3D &&copy_object)
    {
        // Проверка на самоприсваивание
        if(&copy_object==this)
            return*this;

        // Копируем передаваемый объект
        x_cordinate=copy_object.x_cordinate;
        y_cordinate=copy_object.y_cordinate;
        z_cordinate=copy_object.z_cordinate;
        
        vector_arr[0] = x_cordinate;
        vector_arr[1] = y_cordinate;
        vector_arr[2] = z_cordinate;

        std::cout << "Vector Number " << copy_object.Number_vector << " is temporary object. It is will delete later" << std::endl;
        std::cout << "Vector " << this->Number_vector;
        std::cout << " =&move Vector " << copy_object.Number_vector << std:: endl;
        --counter_vector;
        Number_vector = counter_vector;

        logical_value = true; //Необход., чтобы не выводить лишнюю инф. об удалении врем. объекта

        return*this;
    }

    ~Vector3D()  //Деструктор (выводит информацию об удалении объектов).
    {
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
            std::cout<< this->vector_arr[i] << " ";
        }

        std::cout <<"    Number of Vector " << this->Number_vector << std::endl;
    }
};

float *normal_function (std::shared_ptr<Vector3D> const &normal_object)
{   
    std::shared_ptr<Vector3D> function_vector (normal_object);
    std::cout<< "Use Function and creted new shared_ptr" << std::endl;
    std::cout << "Number of shared_ptr = " <<function_vector.use_count() << std::endl;
    
    float variable = sqrtf ((function_vector -> get_x())*(function_vector -> get_x()) + (function_vector -> get_y())*(function_vector -> get_y()) + (function_vector -> get_z())*(function_vector -> get_z()));
    float *normal_vector = new float[3] {(function_vector->get_x())/variable, (function_vector->get_y())/variable, (function_vector->get_z())/variable};
    
    std::cout << "Exit function and delete one shered_ptr" << std::endl;

    return normal_vector;
}

int main ()
{
    std::cout << "------- Simple construction - First Vector ------" << std::endl;
    Vector3D one {10, 20, 30};
	one.print();
    std::cout << std::endl;
    
    std::cout << "------- Construction po umolchaniu - Second Vector ------" << std::endl;
    Vector3D two;
    two.print();
    std::cout << std::endl;
    
    std::cout << "------- Simple Copy - third Vector ------" << std::endl;
    Vector3D three {one};
    three.print();
    std::cout << std::endl;
    
    std::cout << "------- Operator ravno - fourth Vector ------" << std::endl;
    Vector3D four;
    four = two;
    four.print();
    std::cout << std::endl;
    
    std::cout << "------- Construction Move - five Vector ------" << std::endl;
    Vector3D five (std::move(Vector3D {1, 2, 3}));
    five.print();
    std::cout << std::endl;
    
    std::cout << "------- Operator Move and = ------" << std::endl;
    Vector3D six;
    six = std::move(Vector3D(10, 20, 30));
    six.print();
    std::cout << std::endl;
    std::cout << std::endl;

    //Иллюстрация рабты умных указателей shared_ptr
    std::cout << "Created new shared_ptr - seven" << std::endl;
    //Создаем новый умный указатель shared_ptr
    std::shared_ptr<Vector3D> seven = std::make_shared<Vector3D> (3, 4, 10);
    std::cout << "Number of shared_ptr = " <<seven.use_count() << std::endl;

    std::cout << "New example of shared_ptr - eihgt" << std::endl;
    //Повторно используем ранее созданный умный указатель shared_ptr
    std::shared_ptr<Vector3D> eight (seven);
    std::cout << "Number of shared_ptr = " <<seven.use_count() << std::endl;

    std::cout << "Use function normalization" << std::endl;
    //Используем Создаем умный указатель shared_ptr для работы с функцией
    float *nine = normal_function (seven);
    std::cout << "Number of shared_ptr after exit of Function = " <<seven.use_count() << std::endl;
    std::cout << std::endl;

    std::cout << "Print normalization seven: ";
    std::cout << nine[0] << "  " << nine[1] << " " << nine[2] << std::endl;

	return 0;
}