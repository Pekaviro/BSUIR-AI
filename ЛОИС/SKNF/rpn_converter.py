#################################################
#Лабораторная работа №1 по дисциплине Логические основы интеллектуальных систем
#Выполнена студентом группы 321701 БГУИР Перминовой Виктории Вячеславовны
#Данный файл реализует класс для построения обратной польской записи формулы
#5.03.2025 1.0

from typing import List
from input_validator import FormulaValidationError

class ReversePolishNotationConverter:
    _priority = {'!': 5, '/\\': 4, '\\/': 3, '->': 2, '~': 1}
    
    def __init__(self, expression: str):
        self.expression = expression

    def to_reverse_polish_notation(self) -> List[str]:
        result = []
        stack = []
        i = 0
        n = len(self.expression)
        
        while i < n:
            if self.expression[i] == '-' and i + 1 < n and self.expression[i+1] == '>':
                operator = '->'
                i += 2
            elif self.expression[i] == '/' and i + 1 < n and self.expression[i+1] == '\\':
                operator = '/\\'
                i += 2
            elif self.expression[i] == '\\' and i + 1 < n and self.expression[i+1] == '/':
                operator = '\\/'
                i += 2
            elif self.expression[i].isupper():
                var = self.expression[i]
                i += 1
                while i < n and self.expression[i].isdigit():
                    var += self.expression[i]
                    i += 1
                result.append(var)
                continue
            elif self.expression[i] in {'0', '1'}:
                result.append(self.expression[i])
                i += 1
                continue
            else:
                operator = self.expression[i]
                i += 1

            if operator == '(':
                stack.append(operator)
            elif operator == ')':
                while stack and stack[-1] != '(':
                    result.append(stack.pop())
                stack.pop()
            elif operator in self._priority:
                while stack and stack[-1] != '(' and self._priority.get(stack[-1], 0) >= self._priority[operator]:
                    result.append(stack.pop())
                stack.append(operator)
        
        while stack:
            result.append(stack.pop())
        
        return result

    def is_operator(self, token: str) -> bool:
        return token in self._priority

    def get_priority(self, operator: str) -> int:
        return self._priority.get(operator, 0)