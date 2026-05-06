import React , { useState , useEffect } from 'react';
import { Plus, Edit2, Trash2, X } from 'lucide-react';
import TodoData from './todo_3/TodoData';
import Head from '../components/Head';

// Define the data model based on requested fields
interface FormData {
  id: string;
  title: string;
  content: string;
  isPublic: string; // 'public' | 'private'
  food_orange: boolean;
  food_apple: boolean;
  food_banana: boolean;
  food_melon: boolean;
  food_grape: boolean;
  pub_date1: string;
  pub_date2: string;
  pub_date3: string;
  pub_date4: string;
  pub_date5: string;
  pub_date6: string;
  qty1: number | '';
  qty2: number | '';
  qty3: number | '';
  qty4: number | '';
  qty5: number | '';
  qty6: number | '';
}

const initialFormState: Omit<FormData, 'id'> = {
  title: '',
  content: '',
  isPublic: 'public',
  food_orange: false,
  food_apple: false,
  food_banana: false,
  food_melon: false,
  food_grape: false,
  pub_date1: '',
  pub_date2: '',
  pub_date3: '',
  pub_date4: '',
  pub_date5: '',
  pub_date6: '',
  qty1: 0,
  qty2: 0,
  qty3: 0,
  qty4: 0,
  qty5: 0,
  qty6: 0,
};

export default function App() {
  const [items, setItems] = useState<FormData[]>([]);
  const [isDialogOpen, setIsDialogOpen] = useState(false);
  const [currentFormData, setCurrentFormData] = useState<Omit<FormData, 'id'> | FormData>(initialFormState);


  // TODOの取得
  useEffect(() => {
    const fetchTodos = async () => {
      try {
        const response = await fetch('/api/todo_3'); // デフォルトでGETになります
        if (!response.ok) {
          throw new Error(`エラーが発生しました: ${response.status}`);
        }        
        const data = await response.json();    
        const items = TodoData.getItems(data);
        //console.log(data);
        console.log(items);
        setItems(items);
      } catch (error) {
        console.error('Error fetching todos:', error);
      }
    };
    fetchTodos();
  }, []);  
  // Handle form input changes
  const handleChange = (e: React.ChangeEvent<HTMLInputElement | HTMLTextAreaElement>) => {
    const { name, value, type } = e.target;
    
    if (type === 'checkbox') {
      const checked = (e.target as HTMLInputElement).checked;
      setCurrentFormData(prev => ({ ...prev, [name]: checked }));
    } else if (type === 'radio') {
      setCurrentFormData(prev => ({ ...prev, [name]: value }));
    } else {
      setCurrentFormData(prev => ({ ...prev, [name]: value }));
    }
  };

  const handleOpenDialog = (item?: FormData) => {
    if (item) {
      setCurrentFormData(item);
    } else {
      setCurrentFormData(initialFormState);
    }
    setIsDialogOpen(true);
  };

  const handleCloseDialog = () => {
    setIsDialogOpen(false);
    setCurrentFormData(initialFormState);
  };

  const updateTodo = async (todo: Todo) => {
    console.log(todo);
    try {
      const response = await fetch("/api/todo_3/" + todo.id, {
        method: "PUT",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify(todo),
      });
      if (!response.ok) {
        throw new Error(`HTTPエラー: ${response.status}`);
      }
      const result = await response.text();
      console.log("成功:", result);
      //setTodos((prev) => [todo, ...prev]);
    } catch (error) {
      console.error("通信に失敗しました:", error);
    }
  };

  const handleSave = async (e: React.FormEvent) => {
    e.preventDefault();
    if(currentFormData.isPublic === "public") {currentFormData.is_public = 1;} else {currentFormData.is_public = 0;}
    if(currentFormData.food_orange === true) {currentFormData.food_orange = 1;} else {currentFormData.food_orange = 0;}
    if(currentFormData.food_apple === true) {currentFormData.food_apple = 1;} else {currentFormData.food_apple = 0;}
    if(currentFormData.food_banana === true) {currentFormData.food_banana = 1;} else {currentFormData.food_banana = 0;}
    if(currentFormData.food_melon === true) {currentFormData.food_melon = 1;} else {currentFormData.food_melon = 0;}
    if(currentFormData.food_grape === true) {currentFormData.food_grape = 1;} else {currentFormData.food_grape = 0;}
    currentFormData.qty1 = Number(currentFormData.qty1);
    currentFormData.qty2 = Number(currentFormData.qty2);
    currentFormData.qty3 = Number(currentFormData.qty3);
    currentFormData.qty4 = Number(currentFormData.qty4);
    currentFormData.qty5 = Number(currentFormData.qty5);
    currentFormData.qty6 = Number(currentFormData.qty6);
    if ('id' in currentFormData) {
      console.log(currentFormData)
      updateTodo(currentFormData);
      // Edit existing item
      setItems(prevItems => 
        prevItems.map(item => item.id === (currentFormData as FormData).id ? (currentFormData as FormData) : item)
      );
    } else {
      // Add new item
      const newItem: FormData = {
        ...(currentFormData as Omit<FormData, 'id'>),
        id: crypto.randomUUID()
      };
      console.log(newItem)
      try {
        const response = await fetch('/api/todo_3', {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json'
          },
          body: JSON.stringify(newItem)
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

      setItems(prevItems => [...prevItems, newItem]);
    }
    handleCloseDialog();
  };

  const handleDelete = async (id: string) => {
    if (confirm('本当に削除しますか？')) {
      try {
        const response = await fetch("/api/todo_3/" + id, {
          method: "DELETE", // メソッドを DELETE に指定
        });
        if (!response.ok) {
          throw new Error(`削除に失敗しました: ${response.status}`);
        }
        console.log(`${id}番のデータを削除しました`);
        setItems(prevItems => prevItems.filter(item => item.id !== id));
      } catch (error) {
        console.error("エラー発生:", error);
      }      

    }
  };

  return (
    <div className="min-h-screen bg-gray-50 text-gray-900 p-8">
      <Head />
      <div className="max-w-6xl mx-auto space-y-8">
        {/* Header */}
        <header className="flex items-center justify-between">
          <h1 className="text-3xl font-bold tracking-tight text-gray-900">データ一覧</h1>
          <button
            onClick={() => handleOpenDialog()}
            className="flex items-center gap-2 bg-blue-600 hover:bg-blue-700 text-white px-4 py-2 rounded-md font-medium transition-colors"
          >
            <Plus size={20} />
            追加機能 (ダイアログ)
          </button>
        </header>

        {/* List View */}
        <div className="bg-white rounded-lg shadow ring-1 ring-black/5 overflow-hidden">
          {items.length === 0 ? (
            <div className="p-12 text-center text-gray-500">
              データがありません。「追加機能」ボタンから登録してください。
            </div>
          ) : (
            <div className="overflow-x-auto">
              <table className="min-w-full divide-y divide-gray-200">
                <thead className="bg-gray-50">
                  <tr>
                    <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">タイトル</th>
                    <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">公開状態</th>
                    <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">好きなフルーツ (一部)</th>
                    <th className="px-6 py-3 text-left text-xs font-medium text-gray-500 uppercase tracking-wider">登録日1</th>
                    <th className="px-6 py-3 text-right text-xs font-medium text-gray-500 uppercase tracking-wider">操作</th>
                  </tr>
                </thead>
                <tbody className="bg-white divide-y divide-gray-200">
                  {items.map((item) => (
                    <tr key={item.id} className="hover:bg-gray-50 transition-colors">
                      <td className="px-6 py-4 whitespace-nowrap text-sm font-medium text-gray-900">
                        {item.title || "未入力"}
                      </td>
                      <td className="px-6 py-4 whitespace-nowrap text-sm text-gray-500">
                        {item.isPublic === 'public' ? (
                          <span className="inline-flex items-center px-2.5 py-0.5 rounded-full text-xs font-medium bg-green-100 text-green-800">
                            公開
                          </span>
                        ) : (
                          <span className="inline-flex items-center px-2.5 py-0.5 rounded-full text-xs font-medium bg-gray-100 text-gray-800">
                            非公開
                          </span>
                        )}
                      </td>
                      <td className="px-6 py-4 whitespace-nowrap text-sm text-gray-500">
                        {[
                          item.food_apple && '🍎', 
                          item.food_orange && '🍊', 
                          item.food_banana && '🍌', 
                          item.food_melon && '🍈', 
                          item.food_grape && '🍇'
                        ].filter(Boolean).join(' ') || '-'}
                      </td>
                      <td className="px-6 py-4 whitespace-nowrap text-sm text-gray-500">
                        {item.pub_date1 || '-'}
                      </td>
                      <td className="px-6 py-4 whitespace-nowrap text-right text-sm font-medium">
                        <button
                          onClick={() => handleOpenDialog(item)}
                          className="text-indigo-600 hover:text-indigo-900 mr-4"
                          title="編集"
                        >
                          <Edit2 size={18} />
                        </button>
                        <button
                          onClick={() => handleDelete(item.id)}
                          className="text-red-600 hover:text-red-900"
                          title="削除"
                        >
                          <Trash2 size={18} />
                        </button>
                      </td>
                    </tr>
                  ))}
                </tbody>
              </table>
            </div>
          )}
        </div>
      </div>

      {/* Dialog for Add / Edit */}
      {isDialogOpen && (
        <div className="fixed inset-0 z-50 flex items-center justify-center p-4 sm:p-6">
          <div className="fixed inset-0 bg-gray-900/50 backdrop-blur-sm" onClick={handleCloseDialog}></div>
          <div className="relative w-full max-w-4xl max-h-[90vh] bg-white rounded-xl shadow-2xl overflow-hidden flex flex-col">
            {/* Dialog Header */}
            <div className="flex items-center justify-between px-6 py-4 border-b border-gray-200 bg-gray-50">
              <h2 className="text-xl font-bold text-gray-900">
                {'id' in currentFormData ? 'データ編集' : 'データ追加'}
              </h2>
              <button 
                onClick={handleCloseDialog}
                className="p-2 text-gray-400 hover:text-gray-600 hover:bg-gray-200 rounded-full transition-colors"
              >
                <X size={20} />
              </button>
            </div>

            {/* Dialog Body (Scrollable form) */}
            <form id="record-form" onSubmit={handleSave} className="flex-1 overflow-y-auto p-6 space-y-8">
              
              {/* Basic Info Section */}
              <section className="space-y-4">
                <h3 className="text-sm font-semibold text-gray-900 uppercase tracking-wider border-b pb-2">基本情報</h3>
                
                <div className="space-y-4">
                  <div>
                    <label htmlFor="title" className="block text-sm font-medium text-gray-700">タイトル (title)</label>
                    <input
                      type="text"
                      id="title"
                      name="title"
                      value={currentFormData.title}
                      onChange={handleChange}
                      className="mt-1 block w-full rounded-md border-gray-300 shadow-sm focus:border-blue-500 focus:ring-blue-500 sm:text-sm border p-2"
                      required
                    />
                  </div>

                  <div>
                    <label htmlFor="content" className="block text-sm font-medium text-gray-700">内容 (content)</label>
                    <textarea
                      id="content"
                      name="content"
                      rows={4}
                      value={currentFormData.content}
                      onChange={handleChange}
                      className="mt-1 block w-full rounded-md border-gray-300 shadow-sm focus:border-blue-500 focus:ring-blue-500 sm:text-sm border p-2"
                    />
                  </div>

                  <div>
                    <label className="block text-sm font-medium text-gray-700 mb-2">公開設定 (public)</label>
                    <div className="flex gap-4">
                      <label className="inline-flex items-center cursor-pointer">
                        <input
                          type="radio"
                          name="isPublic"
                          value="public"
                          checked={currentFormData.isPublic === 'public'}
                          onChange={handleChange}
                          className="form-radio text-blue-600 focus:ring-blue-500 h-4 w-4"
                        />
                        <span className="ml-2 text-sm text-gray-700">公開</span>
                      </label>
                      <label className="inline-flex items-center cursor-pointer">
                        <input
                          type="radio"
                          name="isPublic"
                          value="private"
                          checked={currentFormData.isPublic === 'private'}
                          onChange={handleChange}
                          className="form-radio text-blue-600 focus:ring-blue-500 h-4 w-4"
                        />
                        <span className="ml-2 text-sm text-gray-700">非公開</span>
                      </label>
                    </div>
                  </div>
                </div>
              </section>

              {/* Checkboxes Section */}
              <section className="space-y-4">
                <h3 className="text-sm font-semibold text-gray-900 uppercase tracking-wider border-b pb-2">フードプレファレンス</h3>
                <div className="flex flex-wrap gap-4 sm:gap-6">
                  {['orange', 'apple', 'banana', 'melon', 'grape'].map((fruit) => (
                    <label key={`food_${fruit}`} className="inline-flex items-center cursor-pointer">
                      <input
                        type="checkbox"
                        name={`food_${fruit}`}
                        checked={currentFormData[`food_${fruit}` as keyof Omit<FormData, 'id'>] as boolean}
                        onChange={handleChange}
                        className="rounded border-gray-300 text-blue-600 shadow-sm focus:border-blue-500 focus:ring-blue-500 focus:ring-offset-0 h-4 w-4"
                      />
                      <span className="ml-2 text-sm text-gray-700 capitalize">{fruit}</span>
                    </label>
                  ))}
                </div>
              </section>

              {/* Dates Grid Section */}
              <section className="space-y-4">
                <h3 className="text-sm font-semibold text-gray-900 uppercase tracking-wider border-b pb-2">公開日付 (Dates)</h3>
                <div className="grid grid-cols-2 sm:grid-cols-3 gap-4">
                  {[1, 2, 3, 4, 5, 6].map((num) => (
                    <div key={`pub_date${num}`}>
                      <label htmlFor={`pub_date${num}`} className="block text-xs font-medium text-gray-500 mb-1">
                        Date {num} (pub_date{num})
                      </label>
                      <input
                        type="date"
                        id={`pub_date${num}`}
                        name={`pub_date${num}`}
                        value={currentFormData[`pub_date${num}` as keyof Omit<FormData, 'id'>] as string}
                        onChange={handleChange}
                        className="block w-full rounded-md border-gray-300 shadow-sm focus:border-blue-500 focus:ring-blue-500 sm:text-sm border p-2 text-gray-700"
                      />
                    </div>
                  ))}
                </div>
              </section>

              {/* Quantities Grid Section */}
              <section className="space-y-4">
                <h3 className="text-sm font-semibold text-gray-900 uppercase tracking-wider border-b pb-2">数量 (Quantities)</h3>
                <div className="grid grid-cols-2 sm:grid-cols-3 gap-4">
                  {[1, 2, 3, 4, 5, 6].map((num) => (
                    <div key={`qty${num}`}>
                      <label htmlFor={`qty${num}`} className="block text-xs font-medium text-gray-500 mb-1">
                        Quantity {num} (qty{num})
                      </label>
                      <input
                        type="number"
                        id={`qty${num}`}
                        name={`qty${num}`}
                        value={currentFormData[`qty${num}` as keyof Omit<FormData, 'id'>] as number | string}
                        onChange={handleChange}
                        className="block w-full rounded-md border-gray-300 shadow-sm focus:border-blue-500 focus:ring-blue-500 sm:text-sm border p-2"
                      />
                    </div>
                  ))}
                </div>
              </section>

            </form>

            {/* Dialog Footer */}
            <div className="px-6 py-4 border-t border-gray-200 bg-gray-50 flex justify-end gap-3 rounded-b-xl">
              <button
                type="button"
                onClick={handleCloseDialog}
                className="px-4 py-2 border border-gray-300 rounded-md shadow-sm text-sm font-medium text-gray-700 bg-white hover:bg-gray-50 focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-blue-500"
              >
                キャンセル
              </button>
              <button
                type="submit"
                form="record-form"
                className="px-4 py-2 border border-transparent rounded-md shadow-sm text-sm font-medium text-white bg-blue-600 hover:bg-blue-700 focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-blue-500"
              >
                保存する
              </button>
            </div>
          </div>
        </div>
      )}
    </div>
  );
}
