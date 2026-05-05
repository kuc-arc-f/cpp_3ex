
const TodoData = {
  test: "test1",

  getItems: function(items) {
    const ret = [];
    items.forEach(element => {
      let row = element;
      let pub = false
      if(element.public === 1) { pub = true;}
      row.isPublic = pub;
      let foodOrange = false
      if(element.food_orange === 1) { foodOrange = true;}
      row.foodOrange = foodOrange;
      let foodApple = false
      if(element.food_apple === 1) { foodApple = true;}
      row.foodApple = foodApple;
      let foodBanana = false
      if(element.food_banana === 1) { foodBanana = true;}
      row.foodBanana = foodBanana;
      row.pubDate = element.pub_date;
      ret.push(row);
    });
    return ret;
  },

}
export default TodoData;