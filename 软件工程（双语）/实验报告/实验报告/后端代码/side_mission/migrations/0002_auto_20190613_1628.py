
from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('side_mission', '0001_initial'),
    ]

    operations = [
        migrations.AddField(
            model_name='mission',
            name='mis_state',
            field=models.CharField(default='未完成', max_length=3),
        ),
        migrations.AlterField(
            model_name='mission',
            name='mis_content',
            field=models.CharField(max_length=255),
        ),
    ]
