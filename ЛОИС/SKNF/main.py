##################################################
#Лабораторная работа №1 по дисциплине Логические основы интеллектуальных систем
#Выполнена студентом группы 321701 БГУИР Перминовой Виктории Вячеславовны
#Данный файл реализует главную функцию с выводом информации в консоль
#5.03.2025 1.0
import time
from logical_expression import LogicalExpression
from input_validator import InputValidator, FormulaValidationError

def run_test_mode():
    test_cases = [
        {
            "formula": "(A/\\B)",
            "options": [
                "((A\\/B)/\\((A\\/(!B))/\\((!A)\\/B)))",
                "((A\\/B)/\\((!A)\\/(!B)))",
                "(A\\/B)"
            ],
            "correct": 0
        },
        {
            "formula": "(A->B)",
            "options": [
                "((A\\/B)/\\((!A)\\/(!B)))",
                "((!A)\\/B)",
                "(A\\/B)/\\(!A\\/B)"
            ],
            "correct": 1
        },
        {
            "formula": "(A~(!B))",
            "options": [
                "(A\\/B)/\\(!A\\/!B)",
                "(A\\/B)/\\(!A\\/!B)/\\(A\\/!B)/\\(!A\\/B)",
                "((A\\/(!B))/\\((!A)\\/B))"
            ],
            "correct": 0
        },
        {
            "formula": "(!(A\\/B))",
            "options": [
                "(!A\\/!B)",
                "((A\\/(!B))/\\((!A)\\/B))",
                "(((A\\/(!B))/\\((!A)\\/B))/\\((!A)\\/(!B)))"
            ],
            "correct": 2
        },
        {
            "formula": "((A/\\B)\\/(!C))",
            "options": [
                "(((A\\/B\\/(!C))/\\(A\\/(!B)\\/(!C)))/\\((!A)\\/B\\/(!C)))",
                "(!A\\/!B\\/C)/\\(A\\/B\\/C)/\\(A\\/!B\\/C)",
                "((A\\/B)/\\(((!A)\\/(!C))/\\(B\\/C)))",
            ],
            "correct": 0
        }
    ]

    print("\n" + "="*50)
    print("РЕЖИМ ТЕСТИРОВАНИЯ ЗНАНИЙ ПОЛЬЗОВАТЕЛЯ")
    print("Для каждого выражения выберите верный вариант СКНФ")
    print("="*50)

    for i, test in enumerate(test_cases, 1):
        print(f"\nТест {i}: Формула: {test['formula']}")
        for j, option in enumerate(test['options'], 1):
            print(f"{j}. {option}")
        
        while True:
            try:
                answer = int(input("Ваш выбор: ")) - 1
                if 0 <= answer <= 2:
                    break
                print("Пожалуйста, введите число от 1 до 3")
            except ValueError:
                print("Пожалуйста, введите число от 1 до 3")
        
        if answer == test['correct']:
            print("\nВерно!")
        else:
            print(f"\nНеверно. Правильный ответ: {test['correct']+1}")

def run_pcnf_mode():
    while True:
        print("\n" + "=" * 50)
        print("РЕЖИМ ПОСТРОЕНИЯ СКНФ")
        print("Введите 'exit' для возврата в меню")
        expression_str = input("Введите формулу сокращённого языка логики высказываний (операции: /\\, \\/, ~, ->, !): ").strip()
        
        if expression_str.lower() == 'exit':
            return
        
        try:
            InputValidator.validate_formula(expression_str)
            expression = LogicalExpression(expression_str)
        except FormulaValidationError as e:
            print(f"\nОшибка валидации: {e}")
            continue 
        except Exception as e:
            print(f"\nОшибка при обработке формулы: {e}")
            continue

        try:
            pcnf = expression.generate_pcnf()
            print("\nРезультат:")
            print("СКНФ:", pcnf)
        except Exception as e:
            print(f"Ошибка при генерации СКНФ: {e}")

def main():
    while True:
        print("\n" + "="*50)
        print("ГЛАВНОЕ МЕНЮ")
        print("1. Построение СКНФ")
        print("2. Режим тестирования знаний пользователя")
        print("3. Выход")
        print("="*50)
        
        choice = input("Выберите режим: ").strip()
        
        if choice == "1":
            run_pcnf_mode()
        elif choice == "2":
            run_test_mode()
        elif choice == "3":
            print("Завершение работы программы...")
            break
        else:
            print("Некорректный ввод. Пожалуйста, выберите 1, 2 или 3.")

if __name__ == "__main__":
    main()



# def main():
#     start_time = time.time()  # Засекаем начальное время
#     expression = LogicalExpression("(((A\\/B)\\/((C\\/D)/\\(E/\\(F\\/(G\\/H)))))\\/(((I\\/J)\\/(K/\\(L\\/((M/\\N)\\/O))))/\\(P\\/(Q\\/(R\\/(S\\/(T/\\U)))))))")
# # (N\\/(O\\/(P\\/(Q\\/(R\\/(S\\/(T\\/(U\\/(V\\/(W\\/(X\\/(Y\\/Z))))))))

#     pcnf = expression.generate_pcnf()
#     with open('file.txt', 'w', encoding='utf-8') as file:
#         file.write(pcnf)


#     end_time = time.time()  # Засекаем конечное время
#     execution_time = end_time - start_time  # Вычисляем время выполнения
#     print(f"Время выполнения: {execution_time} секунд")

# if __name__ == "__main__":
#     main()