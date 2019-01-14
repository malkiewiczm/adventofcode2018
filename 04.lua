log = {}
for line in io.lines('in.txt') do
   table.insert(log, line)
end

table.sort(log)

sleeps = {}
last_awake = 0

for lineno, line in ipairs(log) do
   year, month, day, hour, minute, action = line:match('%[(%d+)-(%d+)-(%d+) (%d+):(%d+)%] (%a)')
   if action == 'G' then
	  garbage, guard = line:match('(.*) #(%d+)')
   elseif action == 'f' then
	  last_awake = minute
   else
	  if not sleeps[guard] then
		 sleeps[guard] = {}
		 for i=0,59 do
			sleeps[guard][i] = 0
		 end
	  end
	  for i=last_awake,minute-1 do
		 sleeps[guard][i] = sleeps[guard][i] + 1
	  end
   end
end

for guard, arr in pairs(sleeps) do
   local sum = 0
   for k, v in ipairs(arr) do
	  sum = sum + v
   end
   print(guard .. ' = ' ..  sum)
end
