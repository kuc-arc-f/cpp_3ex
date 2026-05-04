import React, { useState, useEffect } from 'react';
import { Trash2, Edit2, Lock, Globe, Calendar, Tag } from 'lucide-react';
import { Todo } from './types';

interface TodoCardProps {
  todo: Todo;
  onDelete: (id: string) => void;
  onEdit: (todo: Todo) => void;
}

export function TodoCard({ todo, onDelete, onEdit }: TodoCardProps) {
  const activeFoods = [];
  if (todo.foodOrange) activeFoods.push('オレンジ');
  if (todo.foodApple) activeFoods.push('りんご');
  if (todo.foodBanana) activeFoods.push('バナナ');

  return (
    <div className="bg-white rounded-xl shadow-sm border border-slate-200 p-5 hover:shadow-md transition-shadow relative group flex flex-col h-full">
      <div className="absolute top-4 right-4 flex space-x-1 opacity-0 group-hover:opacity-100 transition-all focus-within:opacity-100">
        <button
          onClick={() => onEdit(todo)}
          className="p-2 text-slate-300 hover:text-blue-500 hover:bg-blue-50 rounded-full transition-all focus:outline-none focus:ring-2 focus:ring-blue-500"
          title="編集"
        >
          <Edit2 className="w-5 h-5" />
        </button>
        <button
          onClick={() => onDelete(todo.id)}
          className="p-2 text-slate-300 hover:text-red-500 hover:bg-red-50 rounded-full transition-all focus:outline-none focus:ring-2 focus:ring-red-500"
          title="削除"
        >
          <Trash2 className="w-5 h-5" />
        </button>
      </div>

      <div className="flex items-center space-x-2 mb-3 pr-20">
        {todo.isPublic ? (
          <span className="flex items-center text-xs font-medium text-emerald-700 bg-emerald-100 px-2 py-1 rounded-full">
            <Globe className="w-3 h-3 mr-1" /> 公開
          </span>
        ) : (
          <span className="flex items-center text-xs font-medium text-slate-600 bg-slate-100 px-2 py-1 rounded-full">
            <Lock className="w-3 h-3 mr-1" /> 非公開
          </span>
        )}
        {todo.pubDate && (
          <span className="flex items-center text-xs font-medium text-indigo-700 bg-indigo-100 px-2 py-1 rounded-full">
            <Calendar className="w-3 h-3 mr-1" /> {todo.pubDate}
          </span>
        )}
      </div>

      <h3 className="text-lg font-semibold text-slate-900 mb-1">{todo.title}</h3>
      <p className="text-sm text-slate-600 mb-4 flex-grow">{todo.content || <span className="italic text-slate-400">内容なし</span>}</p>

      <div className="space-y-3 mt-auto pt-4 border-t border-slate-100">
        {activeFoods.length > 0 && (
          <div className="flex items-start">
            <Tag className="w-4 h-4 text-slate-400 mt-0.5 mr-2 flex-shrink-0" />
            <div className="flex flex-wrap gap-1.5">
              {activeFoods.map(food => (
                <span key={food} className="text-xs px-2 py-0.5 bg-orange-50 text-orange-700 rounded-md border border-orange-100">
                  {food}
                </span>
              ))}
            </div>
          </div>
        )}

        <div className="grid grid-cols-3 gap-2 text-center text-xs">
          <div className="bg-slate-50 rounded p-1.5 border border-slate-100">
            <span className="block text-slate-400 mb-0.5">Qty 1</span>
            <span className="font-medium text-slate-700">{todo.qty1}</span>
          </div>
          <div className="bg-slate-50 rounded p-1.5 border border-slate-100">
            <span className="block text-slate-400 mb-0.5">Qty 2</span>
            <span className="font-medium text-slate-700">{todo.qty2}</span>
          </div>
          <div className="bg-slate-50 rounded p-1.5 border border-slate-100">
            <span className="block text-slate-400 mb-0.5">Qty 3</span>
            <span className="font-medium text-slate-700">{todo.qty3}</span>
          </div>
        </div>
      </div>
    </div>
  );
}
