#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

template <typename T1, typename T2>
class Pair
{
public:
    Pair() {}
    Pair(const T1& name, const T2& cost) : name(name), cost(cost) {}

    void displayPair() const
    {
        std::cout << name << ": " << cost << std::endl;
    }

    void savePairToFile(std::ofstream& outFile) const
    { student
        outFile << name << " " << cost << " ";
    }

private:
    T1 name;
    T2 cost;
};

class Product
{
public:
    Product(const std::string& name, double cost, int quantity)
        : name(name), cost(cost), quantity(quantity) {}

    ~Product() {}

    const std::string& getName() const
    {
        return name;
    }

    double getCost() const
    {
        return cost;
    }

    int getQuantity() const
    {
        return quantity;
    }

    void setName(const std::string& newName)
    {
        name = newName;
    }

    void setCost(double newCost)
    {
        cost = newCost;
    }

    void setQuantity(int newQuantity)
    {
        quantity = newQuantity;
    }

    virtual void displayInfo() const
    {
        std::cout << "Продукт: " << name << ", цена: " << cost << ", количество: " << quantity << std::endl;
    }

    void saveToFile(std::ofstream& outFile) const
    {
        outFile << name << " " << cost << " " << quantity << " ";
    }

    static bool compareByCost(const Product* product1, const Product* product2)
    {
        return product1->getCost() < product2->getCost();
    }

private:
    std::string name;
    double cost;
    int quantity;
};

class Bakery : public Product
{
public:
    void displayInfo() const override
    {
        std::cout << "Выпечка: " << name << ", цена: " << cost << ", количество: " << quantity << std::endl;
    }
private:
    std::string name;
    double cost;
    int quantity;
};

class Meat : public Product
{
public:
    void displayInfo() const override
    {
        std::cout << "Мясо: " << name << ", цена: " << cost << ", количество: " << quantity << std::endl;
    }
private:
    std::string name;
    double cost;
    int quantity;
};

void modifyProduct(Product* product)
{
    std::cout << "Продукт найден. Что вы хотите изменить?" << std::endl;
    std::cout << "1. Название" << std::endl;
    std::cout << "2. Цену" << std::endl;
    std::cout << "3. Количество " << std::endl;

    int choice;
    std::cout << "Введите ваш выбор: ";
    std::cin >> choice;

    switch (choice)
    {
    case 1:
    {
        std::string newName;
        std::cout << "Введите новое наименование: ";
        std::cin >> newName;
        product->setName(newName);
        break;
    }
    case 2:
    {
        double newCost;
        std::cout << "Введите новую цену: ";
        std::cin >> newCost;
        product->setCost(newCost);
        break;
    }
    case 3:
    {
        int newQuantity;
        std::cout << "Введите новое количество: ";
        std::cin >> newQuantity;
        product->setQuantity(newQuantity);
        break;
    }
    default:
        std::cout << "Неверный выбор." << std::endl;
    }
}

void saveProductsToFile(const std::vector<Product*>& products, const std::string& filename)
{
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        std::cerr << "Ошибка открытия файла для записи." << std::endl;
        return;
    }

    for (const auto* product : products)
    {
        product->saveToFile(outFile);
    }

    outFile.close();
}

int main()
{
    setlocale(LC_ALL, "Russian");

    std::vector<Product*> products;

    int choice;
    std::string filename;

    do
    {
        std::cout << "Меню:" << std::endl;
        std::cout << "1. Добавить продукт" << std::endl;
        std::cout << "2. Изменить данные о продукте" << std::endl;
        std::cout << "3. Удалить продукт" << std::endl;
        std::cout << "4. Найти продукт" << std::endl;
        std::cout << "5. Вывести список продуктов" << std::endl;
        std::cout << "6. Сохранить в файл" << std::endl;
        std::cout << "7. Сортировать по цене" << std::endl;
        std::cout << "8. Выход" << std::endl;

        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            std::string name;
            double cost;
            int quantity;

            std::cout << "Введите данные продукта:" << std::endl;
            std::cout << "Наименование: ";
            std::cin >> name;
            std::cout << "Цена: ";
            std::cin >> cost;
            std::cout << "количество: ";
            std::cin >> quantity;

            products.push_back(new Product(name, cost, quantity));

            break;
        }
        case 2:
        {
            std::string name;
            double cost;
            std::cout << "Введите данные продукта для изменения:" << std::endl;
            std::cout << "Наименование: ";
            std::cin >> name;
            std::cout << "Цена: ";
            std::cin >> cost;

            auto it = std::find_if(products.begin(), products.end(), [&](const Product* product)
                {
                    return product->getName() == name && product->getCost() == cost;
                });

            if (it != products.end())
            {
                modifyProduct(*it);
            }
            else
            {
                std::cout << "Продукт не найден." << std::endl;
            }

            break;
        }
        case 3:
        {
            std::string name;
            double cost;
            std::cout << "Введите данные продукта для удаления:" << std::endl;
            std::cout << "Наименование: ";
            std::cin >> name;
            std::cout << "Цена: ";
            std::cin >> cost;

            auto it = std::find_if(products.begin(), products.end(), [&](const Product* product)
                {
                    return product->getName() == name && product->getCost() == cost;
                });

            if (it != products.end())
            {
                delete* it;
                products.erase(it);
                std::cout << "Продукт удален." << std::endl;
            }
            else
            {
                std::cout << "Продукт не найден." << std::endl;
            }

            break;
        }
        case 4:
        {
            std::string name;
            double cost;
            std::cout << "Введите данные продукта для поиска:" << std::endl;
            std::cout << "Наименование: ";
            std::cin >> name;
            std::cout << "Цена: ";
            std::cin >> cost;

            auto it = std::find_if(products.begin(), products.end(), [&](const Product* product)
                {
                    return product->getName() == name && product->getCost() == cost;
                });

            if (it != products.end())
            {
                (*it)->displayInfo();
            }
            else
            {
                std::cout << "Продукт не найден." << std::endl;
            }

            break;
        }
        case 5:
        {
            std::cout << "Список продуктов:" << std::endl;
            for (const auto* product : products)
            {
                product->displayInfo();
            }
            break;
        }
        case 6:
        {
            std::cout << "Введите имя файла для сохранения данных: ";
            std::cin >> filename;
            saveProductsToFile(products, filename);
            break;
        }
        case 7:
        {
            std::sort(products.begin(), products.end(), Product::compareByCost);
            std::cout << "Список продуктов отсортирован по цене." << std::endl;
            break;
        }
        case 8:
            std::cout << "Выход." << std::endl;
            break;
        default:
            std::cout << "Неверный выбор." << std::endl;
        }
    } while (choice != 8);

    for (const auto* product : products)
    {
        delete product;
    }

    return 0;
}