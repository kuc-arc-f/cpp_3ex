import React from 'react';
import { Route, Routes } from 'react-router';
console.log('#app.tsx');

import Home from './client/home';
import About from './client/about';
import Login from './client/login';
import Todo_2 from './client/todo_2';
import Todo_3 from './client/todo_3';

function App() {
  return (
    <Routes>
      <Route path='/' element={<Home />} />
      <Route path="/about" element={<About />} />      
      <Route path="/login" element={<Login />} />      
      <Route path="/todo_2" element={<Todo_2 />} />
      <Route path="/todo_3" element={<Todo_3 />} />
    </Routes>
  );
}

export default App;
