import React , { useState , useEffect } from 'react';
import { PlusCircle, StretchHorizontal } from 'lucide-react';
import { Todo } from './todo_2/types';
import { TodoDialog } from './todo_2/TodoDialog';
import { TodoCard } from './todo_2/TodoCard';
import TodoData from './todo_2/TodoData';
import Head from '../components/Head';

export default function App() {
  const [todos, setTodos] = useState<Todo[]>([]);
  const [isDialogOpen, setIsDialogOpen] = useState(false);
  const [editingTodo, setEditingTodo] = useState<Todo | null>(null);

  // TODOの取得
  useEffect(() => {
    const fetchTodos = async () => {
      try {
        const response = await fetch('/api/todo_2'); // デフォルトでGETになります
        if (!response.ok) {
          throw new Error(`エラーが発生しました: ${response.status}`);
        }        
        const data = await response.json();    
        const items = TodoData.getItems(data);
        //console.log(data);
        console.log(items);
        setTodos(items);
      } catch (error) {
        console.error('Error fetching todos:', error);
      }
    };
    fetchTodos();
  }, []);

  const openAddDialog = () => {
    setEditingTodo(null);
    setIsDialogOpen(true);
  };

  const openEditDialog = (todo: Todo) => {
    setEditingTodo(todo);
    setIsDialogOpen(true);
  };

  const updateTodo = async (todo: Todo) => {
      console.log(todo);
      try {
        const response = await fetch('/api/todo_2/' + todo.id, {
          method: 'PUT',
          headers: {
            'Content-Type': 'application/json'
          },
          body: JSON.stringify(todo)
        });
        if (!response.ok) {
          throw new Error(`HTTPエラー: ${response.status}`);
        }
        const result = await response.text();
        console.log('成功:', result);
        //setTodos((prev) => [todo, ...prev]);
      } catch (error) {
        console.error('通信に失敗しました:', error);
      } 
  }

  const handleSaveTodo = async (todoData: Omit<Todo, 'id' | 'createdAt'>) => {
    if(todoData.isPublic === true) {todoData.isPublic = 1;} else {todoData.isPublic = 0;}
    if (editingTodo) {
      todoData.id = editingTodo.id;
      updateTodo(todoData);
      setTodos((prev) =>
        prev.map((todo) =>
          todo.id === editingTodo.id ? { ...todo, ...todoData } : todo
        )
      );
    } else {
      const todo: Todo = {
        ...todoData,
        id: crypto.randomUUID(),
        createdAt: Date.now(),
      };
      console.log(todo);
      try {
        const response = await fetch('/api/todo_2', {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json'
          },
          body: JSON.stringify(todo)
        });
        if (!response.ok) {
          throw new Error(`HTTPエラー: ${response.status}`);
        }
        const result = await response.text();
        console.log('成功:', result);
        setTodos((prev) => [todo, ...prev]);
      } catch (error) {
        console.error('通信に失敗しました:', error);
      }       
    }
  };

  const handleDeleteTodo = async (id: string) => {
    try {
      const response = await fetch("/api/todo_2/" + id, {
        method: 'DELETE', // メソッドを DELETE に指定
      });
      if (!response.ok) {
        throw new Error(`削除に失敗しました: ${response.status}`);
      }
      console.log(`${id}番のデータを削除しました`);
      setTodos((prev) => prev.filter((todo) => todo.id !== id));
    } catch (error) {
      console.error('エラー発生:', error);
    }    
  };

  return (
    <div className="min-h-screen bg-slate-50 text-slate-900 font-sans pb-20">
      <Head />
      {/* Header */}
      <header className="bg-white border-b border-slate-200 sticky top-0 z-10 shadow-sm">
        <div className="max-w-5xl mx-auto px-4 sm:px-6 lg:px-8 h-16 flex items-center justify-between">
          <div className="flex items-center space-x-2">
            <div className="bg-blue-600 p-2 rounded-lg">
              <StretchHorizontal className="w-5 h-5 text-white" />
            </div>
            <h1 className="text-xl font-bold text-slate-800 tracking-tight">Advanced Tasks</h1>
          </div>
          <button
            onClick={openAddDialog}
            className="inline-flex items-center px-4 py-2 bg-blue-600 text-white text-sm font-medium rounded-lg hover:bg-blue-700 transition-colors shadow-sm focus:outline-none focus:ring-2 focus:ring-blue-500 focus:ring-offset-2"
          >
            <PlusCircle className="w-4 h-4 mr-2" />
            追加
          </button>
        </div>
      </header>

      {/* Main Content */}
      <main className="max-w-5xl mx-auto px-4 sm:px-6 lg:px-8 pt-8">
        {todos.length === 0 ? (
          <div className="text-center py-20 bg-white rounded-2xl border border-dashed border-slate-300">
            <div className="mx-auto w-16 h-16 bg-slate-100 rounded-full flex items-center justify-center mb-4">
              <PlusCircle className="w-8 h-8 text-slate-400" />
            </div>
            <h3 className="text-lg font-medium text-slate-900 mb-1">TODOがありません</h3>
            <p className="text-slate-500 mb-6">新しいタスクを追加してください。</p>
            <button
              onClick={openAddDialog}
              className="inline-flex items-center px-4 py-2 bg-white border border-slate-300 text-slate-700 text-sm font-medium rounded-lg hover:bg-slate-50 transition-colors"
            >
              TODOを追加
            </button>
          </div>
        ) : (
          <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-6">
            {todos.map((todo) => (
              <TodoCard key={todo.id} todo={todo} onDelete={handleDeleteTodo} onEdit={openEditDialog} />
            ))}
          </div>
        )}
      </main>

      {/* Dialog */}
      <TodoDialog
        isOpen={isDialogOpen}
        onClose={() => setIsDialogOpen(false)}
        onSave={handleSaveTodo}
        initialData={editingTodo}
      />
    </div>
  );
}
