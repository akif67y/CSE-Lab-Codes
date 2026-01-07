select rpad(first_name || ' ' || last_name, 20, ' ') full_name
from employees
order by length(first_name || ' ' || last_name) asc;