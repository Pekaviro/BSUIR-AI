##################################################
#Лабораторная работа №1 по дисциплине Логические основы интеллектуальных систем
#Выполнена студентом группы 321701 БГУИР Перминовой Виктории Вячеславовны
#Данный файл реализует функцию построения СКНФ для логического выражения
#5.03.2025 1.0

from typing import Dict, List
from variable_manager import VariableManager
from rpn_converter import ReversePolishNotationConverter
from truth_table_generator import TruthTableGenerator

class LogicalExpression:
    def __init__(self, expression: str):
        self.expression = expression
        self.variable_manager = VariableManager(expression)
        self.rpn_converter = ReversePolishNotationConverter(expression)
        self.rpn = self.rpn_converter.to_reverse_polish_notation()
        self.truth_table_generator = TruthTableGenerator(self.variable_manager.get_variable_map(), self.rpn)

    def generate_truth_table(self) -> Dict[str, int]:
        truth_table = self.variable_manager.get_variable_map().copy()
        final_result, intermediates = self.truth_table_generator.evaluate_expression()
        
        if intermediates:
            last_key = list(intermediates.keys())[-1]
            del intermediates[last_key]
        
        truth_table.update(intermediates)
        truth_table[self.expression] = final_result
        return truth_table

    def generate_pcnf(self):
        truth_table = self.generate_truth_table()
        expression_result = truth_table.get(self.expression, 0)
        variables = list(self.variable_manager.get_variable_map().keys())
        num_combinations = 2 ** len(variables) if variables else 1

        pcnf_clauses = []
        for i in range(num_combinations):
            if not ((expression_result >> i) & 1):
                if not variables:
                    return "(A/\\(!A))"
                
                clause_parts = []
                for var in variables:
                    value = (truth_table[var] >> i) & 1
                    clause_parts.append(f"(!{var})" if value else var)
                
                clause = f"({'\\/'.join(clause_parts)})"
                pcnf_clauses.append(clause)
        
        if not pcnf_clauses:
            return "Не существует"
        
        return f"({'/\\'.join(pcnf_clauses)})"

    def get_expression(self) -> str:
        return self.expression 