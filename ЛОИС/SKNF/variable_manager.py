##################################################
#Лабораторная работа №1 по дисциплине Логические основы интеллектуальных систем
#Выполнена студентом группы 321701 БГУИР Перминовой Виктории Вячеславовны
#Данный файл реализует класс для работы с переменными из выражения
#5.03.2025 1.0

from typing import Dict, List, Set
import re

class VariableManager:
    def __init__(self, expression: str):
        self.expression = expression
        self.variables = self._extract_variables()

    def _extract_variables(self) -> List[str]:
        variables = set()
        i = 0
        n = len(self.expression)
        while i < n:
            if self.expression[i].isupper():
                var = self.expression[i]
                i += 1
                while i < n and self.expression[i].isdigit():
                    var += self.expression[i]
                    i += 1
                variables.add(var)
            else:
                i += 1
        return sorted(variables)

    def get_variable_map(self) -> Dict[str, int]:
        variable_map = {}
        num_vars = len(self.variables)
        if num_vars == 0:
            return {}
        
        num_combinations = 1 << num_vars
        for i, var in enumerate(self.variables):
            shift = num_vars - 1 - i
            mask = 0
            for j in range(num_combinations):
                mask |= ((j >> shift) & 1) << j
            variable_map[var] = mask
        return variable_map