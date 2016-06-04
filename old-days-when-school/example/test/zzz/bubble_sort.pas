var n, i, j, tmp : integer;
var a : array[1..1000] of integer;

begin
	readln(n);
	for i := 1 to n  do
	begin
		read( a[i] );
	end;
	for i := 1 to n-1 do
	begin
		for j := i+1 to n do
		begin
			if a[i] > a[j] then
			begin
				tmp := a[i];
				a[i] := a[j];
				a[j] := tmp;
			end;
		end;
	end;
	for i := 1 to n do
	begin
		writeln( a[i] );
	end;
end.
