##################################################
#Лабораторная работа №1 по дисциплине Логические основы интеллектуальных систем
#Выполнена студентом группы 321701 БГУИР Перминовой Виктории Вячеславовны
#Данный файл реализует класс для построение таблицы истинности
#5.03.2025 1.0

from typing import Dict, List, Tuple

class TruthTableGenerator:
    def __init__(self, variable_map: Dict[str, int], rpn: List[str]):
        self.variable_map = variable_map
        self.rpn = rpn

    def evaluate_expression(self) -> Tuple[int, Dict[str, int]]:
        num_vars = len(self.variable_map)
        num_combinations = 1 << num_vars if num_vars > 0 else 1
        intermediate_results = {}
        final_result = 0
        step_number = 1

        # Pre-allocate intermediate results
        for token in self.rpn:
            if self.is_operator(token):
                intermediate_results[f"step_{step_number} ({token})"] = 0
                step_number += 1

        for i in range(num_combinations):
            stack = []
            step = 1
            for token in self.rpn:
                if token in {'0', '1'}:
                    stack.append(token == '1')
                elif token in self.variable_map:
                    stack.append((self.variable_map[token] >> i) & 1)
                elif self.is_operator(token):
                    op_name = f"step_{step} ({token})"
                    
                    if token == '!':
                        operand = stack.pop()
                        result = self._not(operand)
                    elif token == '/\\':
                        operand2 = stack.pop()
                        operand1 = stack.pop()
                        result = self._and(operand1, operand2)
                    elif token == '\\/':
                        operand2 = stack.pop()
                        operand1 = stack.pop()
                        result = self._or(operand1, operand2)
                    elif token == '->':
                        operand2 = stack.pop()
                        operand1 = stack.pop()
                        result = self._implies(operand1, operand2)
                    elif token == '~':
                        operand2 = stack.pop()
                        operand1 = stack.pop()
                        result = self._equiv(operand1, operand2)
                    
                    intermediate_results[op_name] |= result << i
                    stack.append(result)
                    step += 1
            
            final_result |= stack.pop() << i

        return final_result, intermediate_results

    def _not(self, a: bool) -> bool:
        return not a

    def _and(self, a: bool, b: bool) -> bool:
        return a and b

    def _or(self, a: bool, b: bool) -> bool:
        return a or b

    def _implies(self, a: bool, b: bool) -> bool:
        return (not a) or b

    def _equiv(self, a: bool, b: bool) -> bool:
        return a == b

    def is_operator(self, token: str) -> bool:
        return token in {'!', '/\\', '\\/', '~', '->'}

    def is_operand(self, token: str) -> bool:
        return token[0].isupper() and all(c.isdigit() for c in token[1:])