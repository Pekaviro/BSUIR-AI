% Лабораторная работа №2 по дисциплине Логические основы интеллектуальных систем
% Выполнена студентом группы 321701 БГУИР Перминовой Викторией Вячеславовной
% В файле содержится исходный код для решения задачи: "Два берега реки. На одном из них полицейский с заключённым, мама с дочерьми и отец с сыновьями. Необходимо с помощью плота, вмещающего не более двух человек, переправить всех персонажей на другой берег реки. Управлять плотом могут только полицейский и родители. Заключённого нельзя оставлять ни с одним из членов семьи. Папе не разрешается находиться с дочерьми без присутствия матери. Маме не разрешается находиться с сыновьями без присутствия отца".
% 20.05.2025 1.0

% Списки членов семьи
family([mother, father, daughter1, daughter2, son1, son2]).
daughters([daughter1, daughter2]).
sons([son1, son2]).

% Список тех, кто может управлять плотом
can_steer_list([policeman, mother, father]).

% Предикат для проверки возможности управления
can_steer(Person) :-
    can_steer_list(Steerers),
    member(Person, Steerers).

% Безопасность берега
safe_bank(Bank) :-
    \+ (member(prisoner, Bank),
        (family(F), member(M, F), member(M, Bank)),
        \+ member(policeman, Bank)),
    \+ (member(father, Bank),
        (daughters(D), member(Daughter, D), member(Daughter, Bank)),
        \+ member(mother, Bank)),
    \+ (member(mother, Bank),
        (sons(S), member(Son, S), member(Son, Bank)),
        \+ member(father, Bank)).

% Нормализация состояния
normalize_state([Left, Right, Boat], [SLeft, SRight, Boat]) :-
    sort(Left, SLeft),
    sort(Right, SRight).

% Перемещение
move([Left, Right, left], [NewLeft, NewRight, right]) :-
    select(Steerer, Left, TempLeft),
    can_steer(Steerer),
    (select(Passenger, TempLeft, NewLeft) ; NewLeft = TempLeft),
    ( var(Passenger) 
        -> NewRight = [Steerer | Right] 
        ;  NewRight = [Steerer, Passenger | Right]
    ),
    safe_bank(NewLeft),
    safe_bank(NewRight).

move([Left, Right, right], [NewLeft, NewRight, left]) :-
    select(Steerer, Right, TempRight),
    can_steer(Steerer),
    (select(Passenger, TempRight, NewRight) ; NewRight = TempRight),
    ( var(Passenger) 
        -> NewLeft = [Steerer | Left] 
        ;  NewLeft = [Steerer, Passenger | Left]
    ),
    safe_bank(NewLeft),
    safe_bank(NewRight).

% Поиск решения
solve(State, [State], _) :-
    normalize_state(State, [[], Right, _]),
    sort(Right, Sorted),
    Sorted = [daughter1, daughter2, father, mother, policeman, prisoner, son1, son2].

solve(State, [State | Path], Visited) :-
    move(State, NextState),
    normalize_state(NextState, NormNext),
    \+ member(NormNext, Visited),
    solve(NextState, Path, [NormNext | Visited]).

% Запуск
start :-
    InitialState = [
        [policeman, prisoner, mother, father, daughter1, daughter2, son1, son2],
        [],
        left
    ],
    normalize_state(InitialState, NormInit),
    solve(InitialState, Path, [NormInit]),
    print_path(Path).

% Вывод пути
print_path([]). % База рекурсии: пустой путь
print_path([State | Rest]) :-
    State = [Left, Right, Boat],
    format('Left: ~w, Right: ~w, Boat: ~w~n', [Left, Right, Boat]),
    print_path(Rest).