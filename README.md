# Programação Cientifica
>> Mestrado - Programação Cientifica

Pré-requisitos
  - Instalação do MPI - Link: https://docs.microsoft.com/en-us/message-passing-interface/microsoft-mpi

Atividade 1 
  - Fila estática (queue.h)
  - Pilha estática (stack.h)

Atividade 2
  - Lista ligada dinâmica (linked_list.h)
  - Fila dinâmica herdando da lista ligada (queue_dynamic.h)
  - Pilha dinâmica herdando da lista ligada (stack_dynamic.h)

Atividade 3 e 4
  - Resolver o jogo Puzzle 8 com algoritmos de busca aplicados em árvore n-ária (puzzle.h, tree.h)
  - DFS, BFS, hiil-climbing e A*

Atividade 5
  - Descida do Gradiente (numeric_method.h) 
    - double gradient_descent_a(double x0, double beta, double epsilon);
    - double gradient_descent_b(double x0, double beta, double epsilon);
    - void test_gradient();
    
Atividade 6
  - Integração Numérica (numeric_method.h)
    - double midpoint(std::function<double(double)>f);
    - double trapezoidal(std::function<double(double)>f);
    - double simpson(std::function<double(double)>f);
    - double numeric_square_by_divisions(std::function<double(double)>f, std::function<double(std::function<double(double)>)> numeric_method_func, int divisions);
    - double numeric_square_by_error_rate(std::function<double(double)>f, std::function<double(std::function<double(double)>)> numeric_method_func, std::function<double(std::function<double(double)>, int)> numeric_method_error_func, double error_rate);
    - double midpoint_error(std::function<double(double)>f, int divisions);
    - double trapezoidal_error(std::function<double(double)>f, int divisions);
    - double simpson_error(std::function<double(double)>f, int divisions);
    - void test_adaptative_square();
    
Atividade 7
  - Monte Carlo (numeric_method.h)
    - double monte_carlo_by_attempts(std::function<double(double)>f, IntegrateRange<double> range, int attempts);
    - double monte_carlo_by_error_rate(std::function<double(double)>f, IntegrateRange<double> range, double error);
    - double monte_carlo_volume_by_attempts(std::function<double(double, double, double)>f, IntegrateRange<double>* ranges, int attempts);
    - double monte_carlo_volume_error_rate(std::function<double(double, double, double)>f, IntegrateRange<double>* ranges, double error);
    - double monte_carlo_error(std::function<double(double)>f, IntegrateRange<double> range, int attempts);
    - double monte_carlo_volume_error(std::function<double(double, double, double)>f, IntegrateRange<double>* ranges, int attempts);
    - void test_monte_carlo();
    
Atividade 8
  - Monte Carlo com MPI (numeric_method.h)
    - void monte_carlo_by_attempts_distributed(std::function<double(double)>f, IntegrateRange<double> range, int attempts);
    - void monte_carlo_volume_by_attempts_distributed(std::function<double(double, double, double)>f, IntegrateRange<double>* ranges, int attempts);
    - void test_monte_carlo_distributed();
  
Atividade 9
  - Quadratura Numérica (numeric_method.h) com Open MP
    - double numeric_square_by_divisions_distributed(std::function<double(double)>f, IntegrateRange<double> range, std::function<double(std::function<double(double)>, IntegrateRange<double>)> numeric_method_func, int divisions);
    - double numeric_square_by_error_rate_distributed(std::function<double(double)>f, IntegrateRange<double> range, std::function<double(std::function<double(double)>, IntegrateRange<double>)> numeric_method_func, std::function<double(std::function<double(double)>, IntegrateRange<double>, int)> numeric_method_error_func, double error_rate);
