set project id var:
gcloud config set project causal-block-97013

https://codelabs.developers.google.com/codelabs/cloud-run-hello/#3
build:
gcloud builds submit --tag gcr.io/causal-block-97013/generatehero

send to cloud run:
gcloud run deploy generatehero \
  --image gcr.io/causal-block-97013/generatehero \
  --platform managed \
  --region us-central1 \
  --allow-unauthenticated

run in shell:
docker run -d -p 8080:8080 gcr.io/causal-block-97013/generatehero