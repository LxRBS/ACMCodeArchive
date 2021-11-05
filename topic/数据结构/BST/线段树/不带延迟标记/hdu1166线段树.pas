program hdu1166;//比C++慢

const
  MAXSIZE = 400005;

type
  int = longint;//32位整型
  llt = int64;  //64位整型

type
  node_t = record
    mData:llt; //数据，此处为区间和
    mLazy:llt; //延迟标记
  end;

var
  STree : array [0..MAXSIZE] of node_t;

function lson(x:int):int;
begin
  lson := x + x;
end;

function rson(x:int):int;
begin
  rson := x + x + 1;
end;

//信息上传
procedure _pushUp(t:int);
begin
  STree[t].mData := STree[lson(t)].mData + STree[rson(t)].mData;
end;

//信息下传
procedure _pushDown(t,s,e:int);
var
  son,m:int;
  tmp:llt;
begin
  if STree[t].mLazy = 0 then exit;

  tmp := STree[t].mLazy;
  STree[t].mLazy := 0;

  m := ( s + e ) div 2;

  son := lson(t);
  STree[son].mData := STree[son].mData + tmp * llt( m - s + 1 );
  STree[son].mLazy := STree[son].mLazy + tmp;

  son := rson(t);
  STree[son].mData := STree[son].mData + tmp * llt( e - m );
  STree[son].mLazy := STree[son].mLazy + tmp;
end;

//建树, t为节点,[s,e]为t所代表的区间
procedure build(t,s,e:int);
var m:int;
begin
  STree[t].mLazy := 0;

  if s = e then
  begin
    read(m);
    STree[t].mData := llt(m);
    exit;
  end;

  m := ( s + e ) div 2;
  build(lson(t),s,m);
  build(rson(t),m+1,e);
  _pushUp(t);
end;

//将源数组[a,b]区间内的所有数增加delta
//t为节点,[s,e]为t所代表的区间
procedure modify(t,s,e,a,b,delta:int);
var
  m:llt;
begin
  if ( a <= s ) and ( e <= b ) then
  begin
    STree[t].mLazy := STree[t].mLazy + llt(delta);
    STree[t].mData := STree[t].mData + llt(delta) * llt( e - s + 1 );
    exit;
  end;

  _pushDown(t,s,e);
  m := ( s + e ) div 2;
  if a <= m then modify(lson(t),s,m,a,b,delta);
  if m < b then modify(rson(t),m+1,e,a,b,delta);
  _pushUp(t);
end;

//查询源数组[a,b]的区间特征值
function query(t,s,e,a,b:int):llt;
var
  m:int;
begin
  if ( a <= s ) and ( e <= b ) then
  begin
    query := STree[t].mData;
    exit;
  end;

  _pushDown(t,s,e);
  m := ( s + e ) div 2;
  query := 0;
  if a <= m then query := query + query(lson(t),s,m,a,b);
  if m < b then query := query + query(rson(t),m+1,e,a,b);
end;

procedure dispNode(t,s,e:int);
var m:int;
begin
  writeln('node: ',t,' [',s,',',e,'] ',STree[t].mData);
  if s = e then exit;
  m := ( s + e ) div 2;
  dispNode(lson(t),s,m);
  dispNode(rson(t),m+1,e);
end;

var
  kase,nofkase:int;
  N:int;
  cmd:char;
  tstr:string;
  a,b:int;
  i:int;
begin
  readln(nofkase);
  for kase:=1 to nofkase do
  begin
    writeln('Case ',kase,':');

    readln(N);
    build(1,1,N);

    readln();
    while true do
    begin
      read(cmd);
      if 'E' = cmd then begin
        readln(tstr);
        break;
      end;

      if 'Q' = cmd then
      begin
        for i:=1 to 4 do read(cmd);
        readln(a,b);
        writeln(query(1,1,N,a,b));
      end
      else if 'S' = cmd then
      begin
        read(cmd,cmd);
        readln(a,b);
        modify(1,1,N,a,a,-b);
      end
      else begin
        read(cmd,cmd);
        readln(a,b);
        modify(1,1,N,a,a,b);
      end;
    end;
  end;
end.

