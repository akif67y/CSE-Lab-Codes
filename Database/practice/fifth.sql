select first_name ||' '|| last_name full_name, hire_date
from EMPLOYEES
where lower(substr(first_name,1,1)) not in('a', 'e', 'i', 'o', 'u') and upper(last_name) not like '%B%' and to_char(hire_date, 'MM') = '11' 
order by full_name;

