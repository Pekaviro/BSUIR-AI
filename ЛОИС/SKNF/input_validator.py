##################################################
# Лабораторная работа №1 по дисциплине Логические основы интеллектуальных систем
# Выполнена студентом группы 321701 БГУИР Перминовой Виктории Вячеславовны
# Данный файл реализует класс для валидации вводимой формулы
# 5.03.2025 1.0

from typing import List
import re

class FormulaValidationError(Exception):
    pass

class InputValidator:
    _operators = {'->', '/\\', '\\/', '~'}
    
    @staticmethod
    def validate_formula(expression: str) -> None:
        if not expression:
            raise FormulaValidationError("Пустое выражение")
        
        if ' ' in expression:
            raise FormulaValidationError("Пробелы в формуле недопустимы")
        
        if len(expression) > 1 and not (expression.startswith('(') and expression.endswith(')')):
            raise FormulaValidationError("Выражение должно быть заключено в скобки")
        
        InputValidator._validate_variables(expression)
        InputValidator._validate_parentheses(expression)
        InputValidator._validate_operations(expression)
    
    @staticmethod
    def _validate_variables(expression: str) -> None:
        i = 0
        n = len(expression)
        while i < n:
            if expression[i] == '!':
                if i > 0 and expression[i-1] != '(':
                    raise FormulaValidationError("Отрицание должно быть заключено в скобки")
                i += 1
            elif i+1 < n and ((expression[i] == '-' and expression[i+1] == '>') or \
                              (expression[i] == '/' and expression[i+1] == '\\') or \
                              (expression[i] == '\\' and expression[i+1] == '/')):
                i += 2
            elif expression[i].isupper():
                if i+1 < n and expression[i+1].isdigit():
                    raise FormulaValidationError(f"Недопустимое имя переменной: '{expression[i]}' с цифрами")
                i += 1
            elif expression[i] in {'0', '1', '(', ')'}:
                i += 1
            else:
                raise FormulaValidationError(f"Недопустимый символ: '{expression[i]}'")

    @staticmethod
    def _validate_parentheses(expression: str) -> None:
        balance = 0
        for char in expression:
            if char == '(':
                balance += 1
            elif char == ')':
                balance -= 1
                if balance < 0:
                    raise FormulaValidationError("Несбалансированные скобки")
        if balance != 0:
            raise FormulaValidationError("Несбалансированные скобки")

    @staticmethod
    def _validate_operations(expression: str) -> None:
        stack = []
        i = 0
        n = len(expression)
        
        while i < n:
            if expression[i] == '(':
                stack.append(i)
                i += 1
            elif expression[i] == ')':
                if not stack:
                    raise FormulaValidationError("Несбалансированные скобки")
                start = stack.pop()
                substr = expression[start+1:i]
                if not substr:
                    raise FormulaValidationError("Пустые скобки")
                
                if not InputValidator._is_valid_subexpression(substr):
                    raise FormulaValidationError(f"Некорректное выражение между скобками: '{substr}'")
                i += 1
            else:
                i += 1

    @staticmethod
    def _is_valid_subexpression(substr: str) -> bool:
        if len(substr) == 1 and (substr.isupper() or substr in {'0', '1'}):
            return True
            
        if substr.startswith('!'):
            return InputValidator._is_valid_subexpression(substr[1:])
        
        balance = 0
        op_pos = -1
        op_len = 0
        
        for i in range(len(substr)):
            if substr[i] == '(':
                balance += 1
            elif substr[i] == ')':
                balance -= 1
            elif balance == 0:
                for op in InputValidator._operators:
                    if substr.startswith(op, i):
                        op_pos = i
                        op_len = len(op)
                        break
                if op_pos != -1:
                    break
        
        if op_pos == -1:
            return False
            
        left = substr[:op_pos]
        right = substr[op_pos+op_len:]
        return (InputValidator._is_valid_subexpression(left) and 
                InputValidator._is_valid_subexpression(right))
