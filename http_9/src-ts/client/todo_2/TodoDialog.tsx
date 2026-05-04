import React, { useState, useEffect } from 'react';
import { X, Save } from 'lucide-react';
import { Todo } from './types';

interface TodoDialogProps {
  isOpen: boolean;
  onClose: () => void;
  onSave: (todo: Omit<Todo, 'id' | 'createdAt'>) => void;
  initialData?: Todo | null;
}

export function TodoDialog({ isOpen, onClose, onSave, initialData }: TodoDialogProps) {
  const [title, setTitle] = useState('');
  const [content, setContent] = useState('');
  const [isPublic, setIsPublic] = useState(true);
  const [foodOrange, setFoodOrange] = useState(false);
  const [foodApple, setFoodApple] = useState(false);
  const [foodBanana, setFoodBanana] = useState(false);
  const [pubDate, setPubDate] = useState('');
  const [qty1, setQty1] = useState(0);
  const [qty2, setQty2] = useState(0);
  const [qty3, setQty3] = useState(0);

  // Reset form when opened or initialData changes
  useEffect(() => {
    if (isOpen) {
      if (initialData) {
        setTitle(initialData.title);
        setContent(initialData.content);
        setIsPublic(initialData.isPublic);
        setFoodOrange(initialData.foodOrange);
        setFoodApple(initialData.foodApple);
        setFoodBanana(initialData.foodBanana);
        setPubDate(initialData.pubDate);
        setQty1(initialData.qty1);
        setQty2(initialData.qty2);
        setQty3(initialData.qty3);
      } else {
        setTitle('');
        setContent('');
        setIsPublic(true);
        setFoodOrange(false);
        setFoodApple(false);
        setFoodBanana(false);
        setPubDate('');
        setQty1(0);
        setQty2(0);
        setQty3(0);
      }
    }
  }, [isOpen, initialData]);

  if (!isOpen) return null;

  const handleSubmit = (e: React.FormEvent) => {
    e.preventDefault();
    onSave({
      title,
      content,
      isPublic,
      foodOrange,
      foodApple,
      foodBanana,
      pubDate,
      qty1,
      qty2,
      qty3,
    });
    onClose();
  };

  return (
    <div className="fixed inset-0 z-50 flex items-center justify-center p-4 bg-black/50 backdrop-blur-sm transition-opacity">
      <div className="bg-white rounded-2xl shadow-xl w-full max-w-2xl max-h-[90vh] overflow-y-auto w-full">
        <div className="sticky top-0 z-10 flex items-center justify-between px-6 py-4 border-b border-slate-100 bg-white shadow-sm">
          <h2 className="text-xl font-semibold text-slate-800">
            {initialData ? 'TODOの編集' : '新規TODOの追加'}
          </h2>
          <button
            onClick={onClose}
            className="p-2 text-slate-400 hover:text-slate-600 hover:bg-slate-100 rounded-full transition-colors"
          >
            <X className="w-5 h-5" />
          </button>
        </div>

        <form onSubmit={handleSubmit} className="p-6 space-y-6">
          <div className="space-y-4">
            {/* Title */}
            <div>
              <label htmlFor="title" className="block text-sm font-medium text-slate-700 mb-1">
                タイトル (Title)
              </label>
              <input
                type="text"
                id="title"
                required
                value={title}
                onChange={(e) => setTitle(e.target.value)}
                className="w-full px-4 py-2 border border-slate-300 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-blue-500 transition-colors"
                placeholder="タスクを入力"
              />
            </div>

            {/* Content */}
            <div>
              <label htmlFor="content" className="block text-sm font-medium text-slate-700 mb-1">
                内容 (Content)
              </label>
              <input
                type="text"
                id="content"
                value={content}
                onChange={(e) => setContent(e.target.value)}
                className="w-full px-4 py-2 border border-slate-300 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-blue-500 transition-colors"
                placeholder="詳細な説明"
              />
            </div>
            
            <div className="grid grid-cols-1 md:grid-cols-2 gap-6 pt-2">
              {/* Public/Private Radio */}
              <div>
                <label className="block text-sm font-medium text-slate-700 mb-2">公開設定 (Public)</label>
                <div className="flex space-x-4">
                  <label className="flex items-center space-x-2 cursor-pointer">
                    <input
                      type="radio"
                      name="publicStatus"
                      checked={isPublic}
                      onChange={() => setIsPublic(true)}
                      className="w-4 h-4 text-blue-600 border-slate-300 focus:ring-blue-500"
                    />
                    <span className="text-sm text-slate-700">公開</span>
                  </label>
                  <label className="flex items-center space-x-2 cursor-pointer">
                    <input
                      type="radio"
                      name="publicStatus"
                      checked={!isPublic}
                      onChange={() => setIsPublic(false)}
                      className="w-4 h-4 text-blue-600 border-slate-300 focus:ring-blue-500"
                    />
                    <span className="text-sm text-slate-700">非公開</span>
                  </label>
                </div>
              </div>

              {/* Date */}
              <div>
                <label htmlFor="pubDate" className="block text-sm font-medium text-slate-700 mb-1">
                  公開日/期限 (Date)
                </label>
                <input
                  type="date"
                  id="pubDate"
                  value={pubDate}
                  onChange={(e) => setPubDate(e.target.value)}
                  className="w-full px-4 py-2 border border-slate-300 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-blue-500 transition-colors"
                />
              </div>
            </div>

            <hr className="border-slate-100" />

            {/* Checkboxes */}
            <div>
              <label className="block text-sm font-medium text-slate-700 mb-2">フルーツ選択 (Foods)</label>
              <div className="flex flex-wrap gap-4">
                <label className="flex items-center space-x-2 cursor-pointer bg-slate-50 px-3 py-2 rounded-md border border-slate-200 hover:bg-slate-100 transition-colors">
                  <input
                    type="checkbox"
                    checked={foodOrange}
                    onChange={(e) => setFoodOrange(e.target.checked)}
                    className="w-4 h-4 text-orange-500 border-slate-300 rounded focus:ring-orange-500"
                  />
                  <span className="text-sm text-slate-700">オレンジ (Orange)</span>
                </label>
                <label className="flex items-center space-x-2 cursor-pointer bg-slate-50 px-3 py-2 rounded-md border border-slate-200 hover:bg-slate-100 transition-colors">
                  <input
                    type="checkbox"
                    checked={foodApple}
                    onChange={(e) => setFoodApple(e.target.checked)}
                    className="w-4 h-4 text-red-500 border-slate-300 rounded focus:ring-red-500"
                  />
                  <span className="text-sm text-slate-700">りんご (Apple)</span>
                </label>
                <label className="flex items-center space-x-2 cursor-pointer bg-slate-50 px-3 py-2 rounded-md border border-slate-200 hover:bg-slate-100 transition-colors">
                  <input
                    type="checkbox"
                    checked={foodBanana}
                    onChange={(e) => setFoodBanana(e.target.checked)}
                    className="w-4 h-4 text-yellow-500 border-slate-300 rounded focus:ring-yellow-500"
                  />
                  <span className="text-sm text-slate-700">バナナ (Banana)</span>
                </label>
              </div>
            </div>
            
            <hr className="border-slate-100" />

            {/* Quantities */}
            <div>
              <label className="block text-sm font-medium text-slate-700 mb-2">数量設定 (Quantities)</label>
              <div className="grid grid-cols-3 gap-4">
                <div>
                  <label htmlFor="qty1" className="block text-xs text-slate-500 mb-1">Qty 1</label>
                  <input
                    type="number"
                    id="qty1"
                    value={qty1}
                    onChange={(e) => setQty1(Number(e.target.value))}
                    className="w-full px-3 py-2 border border-slate-300 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-blue-500 transition-colors"
                  />
                </div>
                <div>
                  <label htmlFor="qty2" className="block text-xs text-slate-500 mb-1">Qty 2</label>
                  <input
                    type="number"
                    id="qty2"
                    value={qty2}
                    onChange={(e) => setQty2(Number(e.target.value))}
                    className="w-full px-3 py-2 border border-slate-300 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-blue-500 transition-colors"
                  />
                </div>
                <div>
                  <label htmlFor="qty3" className="block text-xs text-slate-500 mb-1">Qty 3</label>
                  <input
                    type="number"
                    id="qty3"
                    value={qty3}
                    onChange={(e) => setQty3(Number(e.target.value))}
                    className="w-full px-3 py-2 border border-slate-300 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-blue-500 transition-colors"
                  />
                </div>
              </div>
            </div>
          </div>

          <div className="pt-6 flex justify-end space-x-3">
            <button
              type="button"
              onClick={onClose}
              className="px-5 py-2.5 text-sm font-medium text-slate-700 bg-white border border-slate-300 rounded-lg hover:bg-slate-50 focus:outline-none focus:ring-2 focus:ring-slate-200 transition-colors"
            >
              キャンセル
            </button>
            <button
              type="submit"
              className="px-5 py-2.5 text-sm font-medium text-white bg-blue-600 rounded-lg hover:bg-blue-700 focus:outline-none focus:ring-2 focus:ring-blue-500 focus:ring-offset-2 flex items-center shadow-sm transition-colors"
            >
              <Save className="w-4 h-4 mr-2" />
              {initialData ? '更新する' : '登録する'}
            </button>
          </div>
        </form>
      </div>
    </div>
  );
}
