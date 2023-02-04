FROM python:3

WORKDIR /app

COPY * /app/

RUN apt-get update
RUN apt-get -y install gcc
RUN pip install --no-cache-dir -r requirements.txt

RUN chmod +x start_bot.py
RUN chmod +x main
RUN chmod +x random

ENTRYPOINT ["python","start_bot.py"]