# cli_todo_app

Why am I doing this - to learn different data structures.

A lightweight, persistent command-line task manager built using Linked Lists in c++.

### Installation
1. Clone the repo: 'https://github.com/Vaibhav9535/cli_todo_app.git'
2. Compile the code: 'g++ main.cpp -o todo'

### Usage
- Add a task: `./todo --add "Finish documentation"`
- View tasks: `./todo --list`
- Delete a task: `./todo --del [ID]`


## Things learned
- **Linked List:** The tasks are stored in linked list.
- **Heap vs Stack:** The `TodoList` manager lives on the stack, while individual `Task` nodes are dynamically allocated on the heap.
- **RAII:** (Resource Acquisition Is Initialization) - Using the class life-cycle (constructor/destructor) to manage file I/O and memory cleanup.
- **CLI Parsing:** Utilizes `argc` and `argv` to route commands directly from the shell.

## Things to be learned
- **Add task priority levels.**
- **Implement a search function to find tasks by keyword.**
- **Add color-coded output for better readability.**
