
const TodoData = {
  test: "test1",

  getItems: function(items) {
    const ret = [];
    items.forEach(element => {
      let row = element;
      let pub = 'private'
      if(element.is_public === 1) { pub = 'public';}
      row.isPublic = pub;
      //row.pubDate = element.pub_date;
      ret.push(row);
    });
    return ret;
  },

}
export default TodoData;