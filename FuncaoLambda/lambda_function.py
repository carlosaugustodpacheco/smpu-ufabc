# SISTEMA DE MONITORAMENTO PLUVIAL URBANO - TCC UFABC - CARLOS PACHECO
# VERSÃO 1 - Regra de negócio da função Lambda para tratamento do IP Publico
# SMPU MODELO PARA (CIDADE:SÃO PAULO/ REGIÃO: 1 / MÓDULO SMPU: 1 )
import json
import boto3
import requests
from botocore.exceptions import NoCredentialsError, PartialCredentialsError

# Configurações SNS e DynamoDB
sns_client = boto3.client('sns', region_name='sa-east-1')
dynamodb = boto3.resource('dynamodb')
table = dynamodb.Table('WaterLevel')

# Função Lambda Handler
def lambda_handler(event, context):
    url = 'https://7519-2804-14c-1a5-5724-28a1-4e74-dbb3-6fa.ngrok-free.app/smpu01/'

    # Buscar dados da URL (necessario alterar a url pra cada nova sessão do ngrok)
    try:
        response = requests.get(url)
        data = response.text
        
        # Extrair o nível da água
        nivel_da_agua = 'situacao_normal'
        for part in data.split(';'):
            if part.startswith('nivel_da_agua:'):
                nivel_da_agua = part.split(':')[1]
                break

        # Verificar o nível atual armazenado no DynamoDB
        try:
            # Ajuste a chave primária e o valor conforme seu esquema
            response = table.get_item(Key={'Id': 'nivel_agua'})
            stored_level = response.get('Item', {}).get('CurrentLevel', 'situacao_normal')
            
            if nivel_da_agua != stored_level:
                # Atualizar o DynamoDB com o novo nível
                table.put_item(Item={'Id': 'nivel_agua', 'CurrentLevel': nivel_da_agua})
                
                # Enviar alerta SNS
                if nivel_da_agua == 'alerta_leve':
                    message = 'Alerta leve: O nível da água está ligeiramente elevado.'
                elif nivel_da_agua == 'alerta_moderado':
                    message = 'Alerta moderado: O nível da água está significativamente elevado.'
                elif nivel_da_agua == 'alerta_grave':
                    message = 'Alerta grave: O nível da água está crítico!'
                
                sns_client.publish(
                    TopicArn='arn:aws:sns:sa-east-1:431433565792:SMPU01',
                    Message=message,
                    Subject='Alerta de Nível da Água'
                )
        
        except Exception as e:
            print(f'Erro ao acessar ou atualizar o DynamoDB: {str(e)}')
            return {
                'statusCode': 500,
                'body': json.dumps(f'Erro ao acessar ou atualizar o DynamoDB: {str(e)}')
            }

    except Exception as e:
        print(f'Erro ao buscar dados: {str(e)}')
        return {
            'statusCode': 500,
            'body': json.dumps(f'Erro ao buscar dados: {str(e)}')
        }

    return {
        'statusCode': 200,
        'body': json.dumps(f'Verificação concluída. Nível da água atual: {nivel_da_agua}')
    }