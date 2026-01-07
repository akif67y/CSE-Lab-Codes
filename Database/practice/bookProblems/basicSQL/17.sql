select (initcap(first_name) ||' '|| lower(last_name)) NAME, UPPER(job_id) job_id
from EMPLOYEES