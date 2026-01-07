select first_name, salary, commission_pct
from EMPLOYEES
where job_id = 'AD_PRES'
order by COMMISSION_PCT asc, salary DESC