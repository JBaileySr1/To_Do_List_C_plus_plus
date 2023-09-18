#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

// Structure to represent a task
struct Task {
    string description;
    time_t dueDate;
};

// Function to add a task to the to-do list
void addTask(vector<Task>& todoList) {
    Task task;
    cout << "Enter task description: ";
    cin.ignore();
    getline(cin, task.description);
    cout << "Enter due date (YYYY-MM-DD HH:MM): ";
    string dueDateStr;
    getline(cin, dueDateStr);
    struct tm dueDate = {};
    if (strptime(dueDateStr.c_str(), "%Y-%m-%d %H:%M", &dueDate) != nullptr) {
        task.dueDate = mktime(&dueDate);
        todoList.push_back(task);
        cout << "Task added successfully!" << endl;
    }
    else {
        cout << "Invalid date format. Task not added." << endl;
    }
}

// Function to display the to-do list
void displayTasks(const vector<Task>& todoList) {
    if (todoList.empty()) {
        cout << "No tasks in the to-do list." << endl;
    }
    else {
        cout << "To-Do List:" << endl;
        for (size_t i = 0; i < todoList.size(); ++i) {
            cout << "Task #" << i + 1 << ": " << todoList[i].description << endl;
            cout << "Due Date: " << ctime(&todoList[i].dueDate);
        }
    }
}

// Function to set a reminder for a task
void setReminder(const vector<Task>& todoList) {
    displayTasks(todoList);
    if (todoList.empty()) {
        cout << "No tasks to set reminders for." << endl;
        return;
    }

    int taskIndex;
    cout << "Enter the task number for which you want to set a reminder: ";
    cin >> taskIndex;

    if (taskIndex <= 0 || taskIndex > static_cast<int>(todoList.size())) {
        cout << "Invalid task number." << endl;
        return;
    }

    const Task& task = todoList[taskIndex - 1];
    time_t currentTime = time(nullptr);
    if (task.dueDate <= currentTime) {
        cout << "The due date for this task has already passed." << endl;
    }
    else {
        time_t timeToWait = task.dueDate - currentTime;
        cout << "Reminder set! You will be reminded when the task is due." << endl;
        this_thread::sleep_for(chrono::seconds(timeToWait));
        cout << "Reminder: It's time to complete task \"" << task.description << "\"!" << endl;
    }
}

// Function to delete a task
void deleteTask(vector<Task>& todoList) {
    displayTasks(todoList);
    if (todoList.empty()) {
        cout << "No tasks to delete." << endl;
        return;
    }

    int taskIndex;
    cout << "Enter the task number you want to delete: ";
    cin >> taskIndex;

    if (taskIndex <= 0 || taskIndex > static_cast<int>(todoList.size())) {
        cout << "Invalid task number." << endl;
        return;
    }

    todoList.erase(todoList.begin() + taskIndex - 1);
    cout << "Task deleted successfully!" << endl;
}

int main() {
    vector<Task> todoList;
    int choice;

    while (true) {
        cout << "\nOptions:\n";
        cout << "1. Add Task\n";
        cout << "2. Display Tasks\n";
        cout << "3. Set Reminder\n";
        cout << "4. Delete Task\n";
        cout << "5. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addTask(todoList);
            break;
        case 2:
            displayTasks(todoList);
            break;
        case 3:
            setReminder(todoList);
            break;
        case 4:
            deleteTask(todoList);
            break;
        case 5:
            cout << "Exiting the program." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
